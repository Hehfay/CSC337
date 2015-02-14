#include "butterfly_graph.h"
#include "pthread.h"
using namespace std;

void* make_graph(void* size);

int main(int argc, char** argv)
{
  int n;
  int source;
  int destination;
  int result;
  void* thread_graph;
  pthread_t init_thread;

  cout << MESSAGE0;
  do {
    cout << MESSAGE1;
    cin >> n;
    result = (n & (n - 1));
  } while( (n <= 4) || (result != 0) );

  if(pthread_create(&init_thread, NULL, &make_graph, &n) != 0) return THREAD_CREATE_FAILURE;

  do {
    cout << MESSAGE2;
    cin >> source;
  } while ( source > (n - 1) || source < 0 );

  do {
    cout << MESSAGE3;
    cin >> destination;
  } while ( destination > (n - 1) || destination < 0 );

  cout << NUM_PROCS(n);
  cout << SOURCE(source);
  cout << DESTINATION(destination);

  if(pthread_join(init_thread, &thread_graph) != 0) return THREAD_JOIN_FAILURE;

  Butterfly_Graph* graph = static_cast<Butterfly_Graph*>(thread_graph);
  graph->send_message(source, destination);
  return 0;
}

void* make_graph(void* size)
{
  int* ptr = static_cast<int*>(size);
  void* graph = new Butterfly_Graph(*ptr);
  return graph;
}
