//
// Created by wz on 24-1-26.
//
#include <boost/interprocess/detail/workaround.hpp>

//[doc_shared_ptr_explicit
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/smart_ptr/shared_ptr.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/smart_ptr/deleter.hpp>
#include <cassert>
#include "test/get_process_id_name.h"
#include "glog/logging.h"

using namespace boost::interprocess;
//This is type of the object we want to share
class MyType
{};

typedef managed_shared_memory::segment_manager segment_manager_type;
typedef allocator<void, segment_manager_type>  void_allocator_type;
typedef deleter<MyType, segment_manager_type>  deleter_type;
typedef shared_ptr<MyType, void_allocator_type, deleter_type> my_shared_ptr;

int main(int argc, char *argv[]) {
  FLAGS_alsologtostderr = 1;
  FLAGS_minloglevel = 0;
  google::InitGoogleLogging(argv[0]);

  //Remove shared memory on construction and destruction
  struct shm_remove
  {
    //<-
#if 1
    shm_remove() { shared_memory_object::remove(test::get_process_id_name()); }
    ~shm_remove(){ shared_memory_object::remove(test::get_process_id_name()); }
#else
    //->
      shm_remove() { shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
   //<-
#endif
    //->
  } remover;
  //<-
  (void)remover;
  //->

  //<-
#if 1
  managed_shared_memory segment(create_only, test::get_process_id_name(), 4096);
#else
  //->
   managed_shared_memory segment(create_only, "MySharedMemory", 4096);
   //<-
#endif

  //Create a shared pointer in shared memory
  //pointing to a newly created object in the segment
  my_shared_ptr &shared_ptr_instance =
      *segment.construct<my_shared_ptr>("shared ptr")
          //Arguments to construct the shared pointer
          ( segment.construct<MyType>("object to share")()      //object to own
              , void_allocator_type(segment.get_segment_manager())  //allocator
              , deleter_type(segment.get_segment_manager())         //deleter
          );
  assert(shared_ptr_instance.use_count() == 1);

  //Destroy "shared ptr". "object to share" will be automatically destroyed
  segment.destroy_ptr(&shared_ptr_instance);
  return 0;
}