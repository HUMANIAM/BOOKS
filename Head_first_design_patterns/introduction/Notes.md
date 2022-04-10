### Design principles

1- HAS-A can be better than IS-A
- `HAS-A` is a composition relationship, using it when you want't to delegate some behaviors to another class.
- `IS-A` is an inheritance relationship, using it when you need to extend an existing class.

2- It is always a good practice to separate what changes from what stationary `encapsulation`. Separate the interface from the implementation.
   that is can be useful on the long run where you need to change/maintain your software. Don't expose something on your APIS, you think it is related
   to the implementation and can be change in anytime in the future. Program to an interface, not an implementation.

## Strategy Pattern 
what we have been working in this code is a `strategy Pattern` where we have a family of algorithms (behaviors) and make them interchangeable.
where based on different conditions/users you can pick the working algorithm or behavior.

