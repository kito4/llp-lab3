#pragma once

#ifndef _PAGE_H_
#define _PAGE_H

struct page_header {
  mem_size_t page_data_size;
};

struct elements_page_header {
  mem_size_t next_page;
  mem_size_t elements_count;
};

#pragma pack(push, 1)
struct page_headers {
  struct page_header page_header;
  struct elements_page_header elements_header;
};
#pragma pack(pop)

#endif /* _PAGE_H_ */