/* Example code for Think OS.

Copyright 2015 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include "utils.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_CHILDREN 2
#define QUEUE_LENGTH 160000 // максимальный размер очереди

// QUEUE

typedef struct { // структура очереди
  int *array;    // элементы очереди
  int length;    // длина
  int next_in;   // хранит индекс места на вставку
  int next_out;  // индекс места ввыходящего
} Queue;

Queue *make_queue(int length) // создаёт очередь
{
  Queue *queue = (Queue *)malloc(sizeof(Queue)); // выделяем место под очередь
  queue->length = length;                        // заполняем поля
  queue->array =
      (int *)malloc(length * sizeof(int)); // выделяем память под данные
  queue->next_in = 0;                      // заполняем поля
  queue->next_out = 0;                     // заполняем поля
  return queue;
}

int queue_incr(Queue *queue,
               int i) // циклически переходим к следующему элементу очереди
{
  return (i + 1) % queue->length; // модульный + 1
}

int queue_empty(Queue *queue) // проверка пустоты очереди
{
  // queue is empty if next_in and next_out are the same
  return (queue->next_in == queue->next_out);
}

int queue_full(Queue *queue) // проверка достижения максимального количества
                             // элементов в очереди
{
  // queue is full if incrementing next_in lands on next_out
  return (queue_incr(queue, queue->next_in) == queue->next_out);
}

void queue_push(Queue *queue, int item) { // добавление элемента в очередь
  if (queue_full(queue)) { // проверка возможности добавления
    perror_exit("queue is full");
    return;
  }

  queue->array[queue->next_in] = item; // сохраняем новый элемент в памяти
  queue->next_in = queue_incr(
      queue, queue->next_in); // циклически инкрементируем индекс вставки
}

int queue_pop(Queue *queue) { // доставание элемента из очереди
  if (queue_empty(queue)) { // проверка возможности достать элемент из очереди
    perror_exit("queue is empty");
  }

  int item = queue->array[queue->next_out]; // получаем элемент
  queue->next_out = queue_incr(
      queue, queue->next_out); // циклически инкрементируем индекс вытаскивания
  return item;
}

// SHARED

typedef struct { // структура разделений
  Queue *queue;
} Shared;

Shared *make_shared() // создаёт структуру разделения
{
  Shared *shared = check_malloc(
      sizeof(Shared)); // создаём новый элемент, выделев под него место
  shared->queue = make_queue(QUEUE_LENGTH); // создаём очередь
  return shared;
}

// THREAD

pthread_t make_thread(void *(*entry)(void *), Shared *shared) // создаёт поток
{
  int ret;
  pthread_t thread;

  ret =
      pthread_create(&thread, NULL, entry,
                     (void *)shared); // создаём новый поток, передав в качестве
                                      // аргумента структуру разделений
  if (ret != 0) { // проверяем успешность создания
    perror_exit("pthread_create failed");
  }
  return thread;
}

void join_thread(pthread_t thread) // ожидаем завершения выполнения
{
  int ret = pthread_join(thread, NULL); // ожидаем завершения выполнения
  if (ret == -1) { // проверяем успешность ожидания
    perror_exit("pthread_join failed");
  }
}

// PRODUCER-CONSUMER

void *producer_entry(void *arg) // заполняет очередь
{
  int i;
  Shared *shared = (Shared *)arg;
  for (i = 0; i < QUEUE_LENGTH - 1; i++) {
    printf("adding item %d\n", i);
    queue_push(shared->queue, i);
  }
  pthread_exit(NULL); // прирываем выполнение потока
}

void *consumer_entry(void *arg) // вытаскивает элементы из очереди
{
  int i;
  int item;
  Shared *shared = (Shared *)arg;

  for (i = 0; i < QUEUE_LENGTH - 1; i++) {
    item = queue_pop(shared->queue);
    printf("consuming item %d\n", item);
  }
  pthread_exit(NULL); // прирываем выполнение потока
}

// TEST CODE

void queue_test() {
  int i;
  int item;
  int length = 128;

  Queue *queue = make_queue(length);
  assert(queue_empty(queue));
  for (i = 0; i < length - 1; i++) {
    queue_push(queue, i);
  }
  assert(queue_full(queue));
  for (i = 0; i < 10; i++) {
    item = queue_pop(queue);
    assert(i == item);
  }
  assert(!queue_empty(queue));
  assert(!queue_full(queue));
  for (i = 0; i < 10; i++) {
    queue_push(queue, i);
  }
  assert(queue_full(queue));
  for (i = 0; i < 10; i++) {
    item = queue_pop(queue);
  }
  assert(item == 19);
}

void empty_queue_test() {
  int i;
  pthread_t child[NUM_CHILDREN];

  Shared *shared = make_shared();

  child[1] = make_thread(consumer_entry, shared);
  sleep(1);
  child[0] = make_thread(producer_entry, shared);

  for (i = 0; i < NUM_CHILDREN; i++) {
    join_thread(child[i]);
  }
}

void *producer_positive(void *arg)
{
  int i;
  Shared *shared = (Shared *)arg;
  for (i = 0; i < (QUEUE_LENGTH - 1) / 2; i++) {
    queue_push(shared->queue, 1);
  }
  pthread_exit(NULL);
}

void *producer_negative(void *arg)
{
  int i;
  int item;
  Shared *shared = (Shared *)arg;

  for (i = 0; i < (QUEUE_LENGTH - 1) - ((QUEUE_LENGTH - 1) / 2); i++) {
    queue_push(shared->queue, 2);
  }
  pthread_exit(NULL);
}

void thread_safe_test() {
  int i;
  pthread_t child[NUM_CHILDREN];

  Shared *shared = make_shared();

  for (unsigned int k = 0; k < QUEUE_LENGTH; k++) {
    shared->queue->array[k] = 0;
  }

  child[0] = make_thread(producer_positive, shared);
  child[1] = make_thread(producer_negative, shared);

  for (i=0; i<NUM_CHILDREN; i++) {
    join_thread(child[i]);
  }

  int was_zero = 0;
  for (unsigned int k = 0; k < QUEUE_LENGTH; k++) {
    assert(!(was_zero && shared->queue->array[k]));
    was_zero = was_zero || !shared->queue->array[k];
  }
}

int main() {
  thread_safe_test();
  return 0;
}
