#pragma once
#include<malloc.h>
#include <iostream>

class Allocator
{
public:
	explicit Allocator(size_t n);
	~Allocator();

	void* allocate(size_t n);
	void deallocate(void* current_block);


private:
	struct Node
	{
		Node* prev = nullptr;
		Node* next = nullptr;
	};
	Node* m_mem_pool = nullptr;
	Node* m_free_blocks = nullptr;
	Node* m_alloc_blocks = nullptr;
	size_t m_size;
	size_t m_block_size = 32;
	size_t m_block_num = m_size / (m_block_size + sizeof(Node));

};