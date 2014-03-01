#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef LEVEL1_DCACHE_LINESIZE
  #define LEVEL1_DCACHE_LINESIZE 64
#endif

struct foo {
  int x;
  int y __attribute__((aligned(LEVEL1_DCACHE_LINESIZE)));
};

static struct foo f;

void *print_message_function_a(void *ptr);
void *print_message_function_b(void *ptr);

int main(int argc, char *argv[])
{
  pthread_t thread1, thread2;
  cpu_set_t cpuset1, cpuset2;

  CPU_ZERO(&cpuset1);
  CPU_ZERO(&cpuset2);

  CPU_SET(0, &cpuset1);
  CPU_SET(1, &cpuset2);

  pthread_create(&thread1, NULL, print_message_function_a, NULL);
  pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpuset1);

  pthread_create(&thread2, NULL, print_message_function_b, NULL);
  pthread_setaffinity_np(thread2, sizeof(cpu_set_t), &cpuset2);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  return 0;
}

int sum_a(void)
{
  int s = 0;
  int i = 0;

  for (i = 0; i < 1000000; ++i)
    s += f.x;

  return s;
}

void inc_b(void)
{
  int i = 0;

  for (i = 0; i < 1000000; ++i)
    ++f.y;
}

void *print_message_function_a(void *ptr)
{
  int i = 1000;

  while (i--)
  {
    sum_a();
  }

  return NULL;
}

void *print_message_function_b(void *ptr)
{
  int i = 1000;

  while (i--)
  {
    inc_b();
  }

  return NULL;
}
