#
# from: https://discourse.julialang.org/t/efficient-implementations-of-fibonacci-function-with-interesting-results/18123
#
const b = [ BigInt(1) 1; 1 0]

function pow(a,n)   # n > 0 !
    if n == 1
        return a
    else
        c = pow(a, n >> 1)
        if iseven(n)
            return c*c
        else
            return c*c * a
        end
    end
end

# The underlying algorithms run in linear time.
# Using a divide-and-conquer strategy for matrix exponentation we get an algorithm
# running in time O(log n)
# julia> @elapsed(afib(10^9))
#
function afib(n)
    if n <= 0
        return 0
    elseif n == 1
        return 1
    else
        return (pow(b,n+1))[2,2]
    end
end


# Another implementation running in time O(log n) uses for n>1 Dijkstra’s
# recurrence equation:
#    F(2n)   = F(n) ( 2F(n-1) + F(n) )
#    F(2n+1) = F(n)^2 + F(n+1)^2
# and memoization
# julia> @elapsed(fib(10^9))
#
const fibmem = Dict{Int,BigInt}()
function fib(n)
    get!(fibmem, n) do
        if n <= 0
            return BigInt(0)
        elseif n == 1
            return BigInt(1)
        else
            m = n >> 1
            if iseven(n)
                return fib(m)*(2*fib(m-1) + fib(m))
            else
                return fib(m+1)^2 + fib(m)^2
            end
        end
    end
end


# Trivial loop
# julia> @elapsed(lfib(10^9))
#
function lfib(n)    
    a, b = BigInt(1), BigInt(1)
    for _ in 3:n
        a, b = b, a + b
    end
    return b
end
