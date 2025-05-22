def f(x)
  Math.sin(x) - 2 * x - 1
end

def df(x)
  Math.cos(x) - 2
end

def phi(x)
  (Math.sin(x) - 1) / 2.0
end

def bisection(a, b, eps)
  puts "\nМетод половинного деления (a=#{a}, b=#{b}):"
  puts " n |     a     |     b     |  b - a  "
  puts "---+-----------+-----------+---------"

  n = 0
  while (b - a).abs > eps
    c = (a + b) / 2.0
    n += 1
    printf "%2d | %9.6f | %9.6f | %7.5f\n", n, a, b, b - a
    
    f(c) * f(a) < 0 ? b = c : a = c
  end
  
  (a + b) / 2.0
end

def newton(x0, eps)
  puts "\nМетод Ньютона (x0=#{x0}):"
  puts " n |     x_n   |   x_{n+1} | разница"
  puts "---+-----------+-----------+---------"

  n = 0
  x = x0
  loop do
    x_new = x - f(x) / df(x)
    n += 1
    diff = (x_new - x).abs
    printf "%2d | %9.6f | %9.6f | %7.5f\n", n, x, x_new, diff
    
    break if diff <= eps
    x = x_new
  end
  
  x
end

def iteration(x0, eps)
  puts "\nМетод итераций (x0=#{x0}):"
  puts " n |     x_n   |   x_{n+1} | разница"
  puts "---+-----------+-----------+---------"

  n = 0
  x = x0
  loop do
    x_new = phi(x)
    n += 1
    diff = (x_new - x).abs
    printf "%2d | %9.6f | %9.6f | %7.5f\n", n, x, x_new, diff
    
    break if diff <= eps
    x = x_new
  end
  
  x
end

# Основная программа
eps = 1e-4
interval = [-1.5, -1.0]  # Найденный интервал с корнем

puts "Решаем уравнение sin(x) - 2x = 1 с точностью #{eps}"

# Метод половинного деления
root_bisect = bisection(*interval, eps)
puts "\nРезультат (бисекция): x = #{root_bisect.round(6)}"

# Метод Ньютона
root_newton = newton(interval.sum / 2.0, eps)
puts "Результат (Ньютон): x = #{root_newton.round(6)}"

# Метод итераций
root_iter = iteration(interval.sum / 2.0, eps)
puts "Результат (итерации): x = #{root_iter.round(6)}"
