// qt_shared_deque_2.cpp
#include <iostream>
#include <cassert>

#include <limits>

#include "shared_ring_buffer.h"

int main(int argc, char *argv[])
{
  SharedRingBuffer<int> buffer;

  if(!buffer.create(100)){
    std::cerr << "Could not create/attach shared buffer" << std::endl;
    return 1;
  }
 
  // keep prompting for as long as there is space in the buffer
  while(true){
    int value;
    std::cout << "$>" << std::flush;
 
    if(!(std::cin >> value)){
      if(std::cin.eof()){
        break; // Ctrl+D / end of input
      }
      // not a number: clear the error state and discard the bad line
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Please enter an integer." << std::endl;
      continue;
    }
 
    if(buffer.enqueue(value)){
      std::cout << "Enqueued: " << value << std::endl;
    }
    else{
      std::cout << "Buffer is full, nothing more can be enqueued." << std::endl;
      break;
    }
  }
 
  return 0;
}
