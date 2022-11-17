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
    - [x] capacity
      - [x] size
      - [x] max_size
      - [x] resize
      - [x] capacity
      - [x] empty
      - [x] reserve
    - [x] element access
      - [x] operator[]
      - [x] at
      - [x] front
      - [x] back
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

- [x] stack
  - [x] member functions
    - [x] constructor
    - [x] destructor
    - [x] operator=
    - [x] element access
      - [x] top
    - [x] capacity
      - [x] empty
      - [x] size
    - [x] modifiers
      - [x] push
      - [x] pop
  - [x] non-member functions overloads
    - [x] relational operators

- [ ] map
  - [ ] member functions
    - [x] constructor
    - [x] destructor
    - [x] operator=
    - [ ] iterators
      - [x] begin
      - [x] end
      - [ ] rbegin
      - [ ] rend
    - [ ] capacity
      - [ ] empty
      - [ ] size
      - [ ] max_size
    - [ ] element access
      - [ ] operator[]
      - [ ] at
    - [ ] modifiers
      - [ ] insert
      - [x] erase
      - [ ] swap
      - [x] clear
    - [ ] observers
      - [ ] key_compare
      - [ ] value_compare
    - [ ] operations
      - [ ] find
      - [ ] count
      - [ ] lower_bound
      - [ ] upper_bound
      - [ ] equal_range
    - [ ] allocator
      - [ ] get_allocator
  - [ ] non-member functions overloads
    - [ ] relational operators
    - [ ] swap

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
- [ ] red-black tree
- [ ] red-black tree iterator

## Tests

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
    - [x] capacity
      - [x] size
      - [x] max_size
      - [x] resize
      - [x] capacity
      - [x] empty
      - [x] reserve
    - [x] element access
      - [x] operator[]
      - [x] at
      - [x] front
      - [x] back
    - [x] modifiers
      - [x] assign
      - [x] push_back
      - [x] pop_back
      - [x] insert
      - [x] erase
      - [x] swap
      - [x] clear
    - [x] non-member functions overloads
      - [x] relational operators
      - [x] swap

- [x] stack
  - [x] member functions
    - [x] constructor
    - [x] operator=
    - [x] element access
      - [x] top
    - [x] capacity
      - [x] empty
      - [x] size
    - [x] modifiers
      - [x] push
      - [x] pop
  - [x] non-member functions overloads
    - [x] relational operators

- [ ] map

- [ ] iterator_traits
- [ ] reverse_iterator
- [ ] enable_if
- [ ] is_integral
- [ ] equal and/or lexicographical_compare
- [ ] pair
- [ ] make_pair