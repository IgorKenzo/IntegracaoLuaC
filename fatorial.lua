-- Fatorial 
function fatorial(x)
    if x == 0 or x == 1 then
        return x
    else
        return x * fatorial(x-1)
    end
end