#include <algorithm>
#include <stack>

template <typename T>
class stack_queue
{
public:
    void push(T node) { stack1_.push(node); }
    T pop()
    {
        if (stack2_.size() != 0)
        {
            /* code */
            T tmp = stack2_.top();
            stack2_.pop();
            return tmp;
        }
        else
        {
            while (stakc1_.size() != 0)
            {
                T tmp = stack1_.top();
                stack2_.push(tmp);
                stack1_.pop();
            }
            return pop();
        }
    }

private:
    std::stack<T> stack1_;
    std::stack<T> stack2_;
}