#include <iostream>
#include <vector>

class MemoryManager {
private:
    std::vector<char> memoryBlock; //represents the memory block
    std::vector<bool> allocationStatus; //tracks allocation status of each block; 1-allocated 0-not allocated
    int blockSize; //stores the size of the memory block

public:
    //Constructor of memory manager class
    MemoryManager(int size) {
        blockSize = size; //initializes blocksize to size entered by user
        //resizes memoryBlock & allocationStatus to blockSize
        memoryBlock.resize(blockSize);
        allocationStatus.resize(blockSize, false); //initializes to 0
    }

    //Destructor of MemoryManager class
    //memory deallocation is handled automatically by the vector's destructor
    //The vector itself will be destructed with no user intervention when the object goes out of scope
    /*~MemoryManager() {}*/

    //returns a pointer to the memory block
    //returns a pointer to the first element in the array which is used internally by the vector
    const char* getMemoryBlock() const {
        return memoryBlock.data();
    }

    void* allocate(int size) {
        int startIndex = findFreeBlock(size); //to find free block of size we need
        if(startIndex==-1){
            compactMemory(); //memory compaction to avoid external fragmentation
            startIndex = findFreeBlock(size);
            //if no memory available even after compaction
            if (startIndex == -1) {
                std::cout << "Memory allocation failed. No free block available." << std::endl;
                return nullptr;
            }
        }

        //updates allocation status to 1 for allocated blocks
        for (int i = startIndex; i < startIndex + size; i++) {
            allocationStatus[i] = true;
        }

        //eturns a void pointer to the starting address of the allocated block, obtained by casting the pointer to the corresponding element in the memoryBlock vector
        // does not check if the pointer type and data pointed by the pointer is same or not
        return reinterpret_cast<void*>(&memoryBlock[startIndex]);
    }

    void deallocate(void* address, int size) {
        char* startAddress = memoryBlock.data();
        char* endAddress = startAddress + blockSize;

        char* deallocationAddress = static_cast<char*>(address);

        //checking if deallocation address is within memory range
        if (deallocationAddress < startAddress || deallocationAddress >= endAddress) {
            std::cout << "Invalid address. Please enter a valid address within the allocated memory range." << std::endl;
            return;
        }

        int startIndex = deallocationAddress - startAddress;

        //updating deallocated blocks to 0
        for (int i = startIndex; i < startIndex + size; i++) {
            allocationStatus[i] = false;
        }


        std::cout << "Memory deallocated." << std::endl;
    }

    //Visual representation of memory block
    void displayMemoryStatus() {
        std::cout << "Memory Block Status:" << std::endl;
        for (int i = 0; i < blockSize; i++) {
            std::cout << "[" << (allocationStatus[i] ? "X" : "-") << "]";
        }
        std::cout << std::endl;
        //Using ternary operator, if allocated then X else -
    }

// used internally to find a sequence of consecutive free memory blocks that can accommodate the requested size.
// It returns the starting index of the free block if found; otherwise, it returns -1
private:
    int findFreeBlock(int size) {
        int startIndex = -1; //initializes to -1
        int consecutiveFreeBlocks = 0; //keeps track of the number of consecutive free blocks encountered

        for (int i = 0; i < blockSize; i++) {
            if (!allocationStatus[i]) {
                if (consecutiveFreeBlocks == 0) {
                    startIndex = i;
                }
                consecutiveFreeBlocks++;
            }
            else {
                consecutiveFreeBlocks = 0;
            }

            if (consecutiveFreeBlocks == size) {
                return startIndex;
            }
        }
        return -1;
    }

    void compactMemory() {
        int count=0;
        for (int i = 0; i < blockSize; i++) {
            if (!allocationStatus[i]) {
                count++;
            }
            if(allocationStatus[i] && count>0){
                allocationStatus[i-count]=1;
                allocationStatus[i]=0;
            }
        }
    }   
};

int main() {
    int blockSize;
    std::cout << "Enter the size of the memory block: ";
    std::cin >> blockSize;

    //instance of class 
    MemoryManager memoryManager(blockSize);

    int choice, size;
    void* address; // user needs just an address

    do {
        std::cout << "Memory Manager Menu:" << std::endl;
        std::cout << "1. Allocate memory" << std::endl;
        std::cout << "2. Deallocate memory" << std::endl;
        std::cout << "3. Display memory status" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter the size to allocate: ";
                std::cin >> size;
                address = memoryManager.allocate(size);
                if (address != nullptr) {
                    std::cout << "Memory allocated at address: " << address << std::endl;
                }
                break;
            case 2:
                std::cout << "Enter the address to deallocate: ";
                std::cin >> address;

                std::cout << "Enter the size to deallocate: ";
                std::cin >> size;

                memoryManager.deallocate(address, size);
                break;
            case 3:
                memoryManager.displayMemoryStatus();
                break;
            case 4:
                std::cout << "Exiting." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}