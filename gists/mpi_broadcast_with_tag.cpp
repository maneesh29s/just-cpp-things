#include <mpi.h>

void broadcast(void *data, int count, MPI_Datatype datatype, int root,
               MPI_Comm communicator, int tag)
{
  int world_rank;
  MPI_Comm_rank(communicator, &world_rank);
  int world_size;
  MPI_Comm_size(communicator, &world_size);

  if (world_rank == root)
  {
    // If we are the root process, send our data to everyone
    int i;
    for (i = 0; i < world_size; i++)
    {
      if (i != world_rank)
      {
        MPI_Send(data, count, datatype, i, tag, communicator);
      }
    }
  }
  else
  {
    // If we are a receiver process, receive the data from the root
    MPI_Recv(data, count, datatype, root, tag, communicator, MPI_STATUS_IGNORE);
  }
}