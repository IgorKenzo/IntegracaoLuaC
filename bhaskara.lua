-- Recebe os coeficientes: a, b, c; nessa ordem
function bhaskara(a, b, c)
    delta = (b^2) - 4*a*c

    if delta > 0  then
        x1 = (-b - math.sqrt(delta))/(2 * a)
        x2 = (-b + math.sqrt(delta))/(2 * a)
        return "x1 = " .. x1 .. "; x2 = " .. x2
    elseif delta == 0 then
        x = (-b + math.sqrt(delta))/(2 * a)
        return "x1 e x2 = " .. x
    else 
        return "Não existe raiz real"
    end
end