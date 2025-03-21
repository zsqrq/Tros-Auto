//
// Created by wz on 24-1-25.
//
#include "boost/interprocess/managed_shared_memory.hpp"
#include "boost/interprocess/managed_mapped_file.hpp"
#include "test/get_process_id_name.h"
#include "glog/logging.h"
#include <cassert>

using namespace boost::interprocess;

class MyClass {};

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

  {
    //Create a managed shared memory
    //<-
#if 1
    managed_shared_memory shm(create_only, test::get_process_id_name(), 1000);
#else
    //->
      managed_shared_memory shm(create_only, "MySharedMemory", 1000);
      //<-
#endif
    //->

    //Check size
    assert(shm.get_size() == 1000);
    //Construct a named object
    MyClass *myclass = shm.construct<MyClass>("MyClass")();
    //The managed segment is unmapped here
    //<-
    (void)myclass;
    //->
  }
  {
    //Now that the segment is not mapped grow it adding extra 500 bytes
    //<-
#if 1
    managed_shared_memory::grow(test::get_process_id_name(), 500);
#else
    //->
      managed_shared_memory::grow("MySharedMemory", 500);
      //<-
#endif
    //->

    //Map it again
    //<-
#if 1
    managed_shared_memory shm(open_only, test::get_process_id_name());
#else
    //->
      managed_shared_memory shm(open_only, "MySharedMemory");
      //<-
#endif
    //->
    //Check size
    assert(shm.get_size() == 1500);
    //Check "MyClass" is still there
    MyClass *myclass = shm.find<MyClass>("MyClass").first;
    assert(myclass != 0);
    //<-
    (void)myclass;
    //->
    //The managed segment is unmapped here
  }

  {
    //Now minimize the size of the segment
    //<-
#if 1
    managed_shared_memory::shrink_to_fit(test::get_process_id_name());
#else
    //->
      managed_shared_memory::shrink_to_fit("MySharedMemory");
      //<-
#endif
    //->

    //Map it again
    //<-
#if 1
    managed_shared_memory shm(open_only, test::get_process_id_name());
#else
    //->
      managed_shared_memory shm(open_only, "MySharedMemory");
      //<-
#endif
    //->
    //Check size
    assert(shm.get_size() < 1000);
    //Check "MyClass" is still there
    MyClass *myclass = shm.find<MyClass>("MyClass").first;
    assert(myclass != 0);
    //The managed segment is unmapped here
    //<-
    (void)myclass;
    //->
  }

  return 0;
}