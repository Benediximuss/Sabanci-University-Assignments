//////////////////////////////////////////////////////
// include Memory Manager and related libraries///////
//////////////////////////////////////////////////////

HeapManager m; // Creating global instance of Memory Manager

void * run(void * id)  // Thread function
{
  int * tid = (int * ) id;

  //  N = 2, Size = 100, two threads are allocating 40 Bytes of memory and uses free
  // then allocates 20 bytes of memory and uses free
  // Sequential way
  // Test area
  int rv = m.myMalloc( * tid, 40); // Allocate 40 Bytes
  	if(rv > -1) // if allocation succesfull
  m.myFree( * tid,rv); // free

  rv = m.myMalloc( *tid, 20);
    if(rv > -1)
  m.myFree( * tid,rv);
	
 }

int main() {

  int N = 2;
  int size = 100;

  pthread_t ids[N];
  int intids[N];
  pthread_t cntr = 0;

  for (int i = 0; i < N; i++) {
    intids[i] = i;
    ids[i] = cntr++;
  }

  m.initHeap(size);

  for (int i = 0; i < N; i++) {
    pthread_create( & ids[i], NULL, run, (void * ) & intids[i]);
  }

  for (int i = 0; i < N; i++) {
    pthread_join(ids[i], NULL);
  }

  cout << "Execution is done" << endl;
  m.print();

  return 0;
}
