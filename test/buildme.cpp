#include <boost/test/unit_test.hpp>
#include <rapidxml_graph.hpp>
#include <mpi.h>

#include <defs.hpp>

BOOST_AUTO_TEST_SUITE( mpiio )


BOOST_AUTO_TEST_CASE( mpiio )
{
   using namespace lmcfd;
   MPI_Init(0,0);
   MPI_Comm comm = MPI_COMM_WORLD;
   int commsize, commrank;
   MPI_Comm_size(comm, &commsize);
   MPI_Comm_rank(comm, &commrank);
   MPI_File mpifile;
   MPI_File_open( comm, "abc.file", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &mpifile);


   // ----------------------------------+
   // Test if file view seek behavior   |
   // ----------------------------------+
   
#define show \
   std::cout << "[" << commrank << "][" << __LINE__ << "] " << tell(mpifile) << std::endl

   using std::string;
   string header("header");
   header += boost::lexical_cast<string>(commrank);

   
   const int N = 3;
   MPI_Aint disp[N] = {0,12,20};
   int blen[N]      = {1,1,1};
   MPI_Datatype filetype;
   MPI_Type_create_hindexed( N, blen, disp, MPI_INT, &filetype); 

   show;

   MPI_File_seek( mpifile,  1,  MPI_SEEK_SET );

   show;

   MPI_File_set_view(mpifile, 0, MPI_INT, filetype, "native", MPI_INFO_NULL);

   show;

//    MPI_File_seek( mpifile,  1,  MPI_SEEK_SET );   show;
//    MPI_File_seek( mpifile,  2,  MPI_SEEK_SET );   show;
//    MPI_File_seek( mpifile,  3,  MPI_SEEK_SET );   show;
   MPI_File_seek( mpifile,  4,  MPI_SEEK_SET );   show;

   MPI_File_seek( mpifile,  1,  MPI_SEEK_SET );   show;
   MPI_File_seek( mpifile,  2,  MPI_SEEK_CUR );   show;

   MPI_File_write(mpifile, blen, 2, MPI_INT, MPI_STATUS_IGNORE);
   show;

   MPI_File_set_view(mpifile, MPI_DISPLACEMENT_CURRENT, MPI_BYTE, MPI_BYTE, "native", MPI_INFO_NULL);
   show;

   MPI_File_write(mpifile, blen, 1, MPI_INT, MPI_STATUS_IGNORE);
   show;


   MPI_File_close(&mpifile);
   MPI_Finalize();
}

BOOST_AUTO_TEST_SUITE_END()
