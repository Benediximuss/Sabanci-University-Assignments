//////////////////////////////////////////////////////
// include Memory Manager and related libraries///////
//////////////////////////////////////////////////////
HeapManager m; // Creating global instance of Memory Manager

void * run(void * id)  // Thread function
{
   int * tid = (int * ) id;
   int rv,rv2 = -1;
  //  N = 5, Size = 100, 5 threads are allocating random Bytes of memory 
  // If allocated, they spend some time with using usleep function then uses free
  // Test area
  int randomSize  = rand() % 30 +1;
  int randomTime = rand() % 3000 +1;

  rv = m.myMalloc(* tid, randomSize);   // if allocated for first request, sleep random time ( do actual job)
  if(rv > -1)
   usleep(randomTime);

  randomSize = rand() % 20 +1;
  randomTime = rand() % 2000  +1;
  rv2 = m.myMalloc(*tid, randomSize); // if allocated for second request, sleep random time ( do actual job)
  if( rv2 > -1)
    usleep(randomTime);

  if(rv > -1 ) // based on return value, free memory
       m.myFree(*tid,rv);

  if(rv2 > -1)
        m.myFree(*tid,rv2);

	
 }

int main() {

  int N = 5;
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
