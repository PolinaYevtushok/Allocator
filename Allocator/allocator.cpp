#include "Allocator.h"

 Allocator::Allocator(size_t n) : m_size(n)
	{
		m_mem_pool = reinterpret_cast<Node*>(malloc(m_size));
		// if m_mem_pool created successful
		if (m_mem_pool)
		{
			Node* current_block = reinterpret_cast<Node*>((char*)m_mem_pool + 0 * (m_block_size + sizeof(Node)));
			for (size_t i = 1; i < m_block_num; ++i)
			{
				Node* current_block_next = reinterpret_cast<Node*>((char*)m_mem_pool + i * (m_block_size + sizeof(Node)));
				//filling free linked list
				if (!m_free_blocks)
					current_block->prev = nullptr;
				else
					current_block->prev = m_free_blocks;
				current_block->next = current_block_next;
				m_free_blocks = current_block;
				current_block = current_block_next;
				//Test
				//std::cout << m_free_blocks->prev << ' ' << m_free_blocks << ' ' << m_free_blocks->next << std::endl;
			}
		}
	}
	Allocator::~Allocator()
	{
		if (m_mem_pool != nullptr)
			delete(m_mem_pool);
	}

	void* Allocator::allocate(size_t n)
	{
		if (n > m_block_size || m_free_blocks == nullptr || m_mem_pool == nullptr)
			return nullptr;

		Node* current_block = m_free_blocks;
		m_free_blocks = current_block->prev;
		m_free_blocks->next = current_block->next;
		//Test
		/*std::cout << "Current: " << std::endl;
		std::cout << current_block->prev << ' ' << current_block << ' ' << current_block->next << std::endl;
		std::cout << "Alloc_before: " << std::endl;
		if (m_alloc_blocks)
			std::cout << m_alloc_blocks->prev << ' ' << m_alloc_blocks << ' ' << m_alloc_blocks->next << std::endl;
		else
			std::cout << "NO" << std::endl;*/

		if (!m_alloc_blocks )
			current_block->prev = nullptr;
		else
		{
			current_block->prev = m_alloc_blocks;
		}	
		current_block->next = nullptr;
		m_alloc_blocks = current_block;
		//Test
		/*std::cout << "Alloc: " << std::endl;
		std::cout << m_alloc_blocks->prev << ' ' << m_alloc_blocks << ' ' << m_alloc_blocks->next << std::endl;*/

		return reinterpret_cast<void*>(reinterpret_cast<char*>(current_block) + sizeof(Node));

	}
	void Allocator::deallocate(void* ptr)
	{
		
		if (ptr > m_mem_pool && ptr < static_cast<void*>(reinterpret_cast<char*>(m_mem_pool) + m_size))
		{
			Node* current_block = reinterpret_cast<Node*>(ptr);
			//Test
			/*std::cout << "Current: " << std::endl;
			std::cout << current_block->prev << ' ' << current_block << ' ' << current_block->next << std::endl;*/

			current_block->prev = current_block->next;;
			//Test
			/*std::cout << "Alloc: " << std::endl;
			std::cout << m_alloc_blocks->prev << ' ' << m_alloc_blocks << ' ' << m_alloc_blocks->next << std::endl;*/

			current_block->prev = m_free_blocks;
			current_block->next = nullptr;
			m_free_blocks->next = current_block;
			//Test
			/*std::cout << "Free: " << std::endl;
			std::cout << m_free_blocks->prev << ' ' << m_free_blocks << ' ' << m_free_blocks->next << std::endl;*/
		}
		else 
			delete(ptr);
	}
