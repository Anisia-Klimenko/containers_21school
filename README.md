# Containers

The standard C++ containers have all a specific usage. 
Let’s re-implement them!

## Mandatory containers

- [x] vector
  - [x] member functions
    - [x] constructors
    - [x] destructor
    - [x] operator=
    - [x] iterators
      - [x] begin
      - [x] end
      - [x] rbegin
      - [x] rend
      - [x] cbegin
      - [x] cend
      - [x] crbegin
      - [x] crend
    - [x] capacity
      - [x] size
      - [x] max_size
      - [x] resize
      - [x] capacity
      - [x] empty
      - [x] reserve
      - [x] shrink_to_fit
    - [x] element access
      - [x] operator[]
      - [x] at
      - [x] front
      - [x] back
      - [x] data
    - [x] modifiers
      - [x] assign
      - [x] push_back
      - [x] pop_back
      - [x] insert
      - [x] erase
      - [x] swap
      - [x] clear
    - [x] allocator
      - [x] get_allocator
    - [x] non-member functions overloads
      - [x] relational operators
      - [x] swap

- [ ] map
- [ ] stack

## Bonus containers

- [ ] set (based on red-black tree)

## Additional implementation

- [x] iterator_traits
- [x] reverse_iterator
- [x] enable_if
- [x] is_integral
- [x] equal and/or lexicographical_compare
- [x] pair
- [x] make_pair