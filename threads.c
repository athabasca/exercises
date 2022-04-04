#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define NREADERS 3
#define NWRITERS 3

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t readerQ = PTHREAD_COND_INITIALIZER;
pthread_cond_t writerQ = PTHREAD_COND_INITIALIZER;

int readers = 0;
int writers = 0;

void * reader(void * arg) {
	pthread_mutex_lock(&m);
	while (!(writers == 0)) {
		pthread_cond_wait(&readerQ, &m);
	}
	readers++;
	pthread_mutex_unlock(&m);

	// Read
	
	pthread_mutex_lock(&m);
	if (--readers == 0) {
		pthread_cond_signal(&writerQ);
	}
	pthread_mutex_unlock(&m);

	return 0;
}

void * writer(void * arg) {
	pthread_mutex_lock(&m);
	while(!((readers == 0) && (writers == 0))) {
		pthread_cond_wait(&writerQ, &m);
	}
	writers++;

	// Write
	
	pthread_mutex_lock(&m);
	writers--;
	pthread_cond_signal(&writerQ);
	pthread_cond_broadcast(&readerQ);
	pthread_mutex_unlock(&m);
	
	return 0;
}

int main(void) {
	pthread_t threads[NREADERS + NWRITERS];
	int i, error;

	for (i = 0; i < NREADERS; i++) {
		if ((error = pthread_create(
			&threads[i],
			0,
			reader,
			0
		))) {
			fprintf(stderr, "pthread_create: %s", strerror(error));
			exit(1);
		}
	}

	for (; i < NREADERS + NWRITERS; i++) {
		if ((error = pthread_create(
			&threads[i],
			0,
			writer,
			0
		))) {
			fprintf(stderr, "pthread_create: %s", strerror(error));
			exit(1);
		}
	}	

	for (i = 0; i < NREADERS + NWRITERS; i++) {
		pthread_join(threads[i], 0);
	}

	return 0;
}

