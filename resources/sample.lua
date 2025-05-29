function fibonacci(val)
    if val <= 0 then
        return 0;
    elseif val == 1 then
        return 1;
    end
    return fibonacci(val - 1) + fibonacci(val - 2)
end

function multi(val1, val2)
    return val1 + val2, val1 * val2, "aiueo"
end
