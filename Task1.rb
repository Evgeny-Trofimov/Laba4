def f(x) = Math.sin(x) - 2*x - 1
def df(x) = Math.cos(x) - 2
def phi(x) = (Math.sin(x) - 1)/2.0

def bisect(a, b, eps)
  puts "\nБисекция:"
  c = (a+b)/2.0
  while (b-a).abs > eps
    f(c)*f(a) < 0 ? b = c : a = c
    c = (a+b)/2.0
    puts "a=#{a.round(6)} b=#{b.round(6)}"
  end
  c
end

def newton(x, eps)
  puts "\nНьютон:"
  loop do
    x_new = x - f(x)/df(x)
    puts "x=#{x.round(6)}"
    break x if (x_new - x).abs <= eps
    x = x_new
  end
end

def iterate(x, eps)
  puts "\nИтерации:"
  loop do
    x_new = phi(x)
    puts "x=#{x.round(6)}"
    break x if (x_new - x).abs <= eps
    x = x_new
  end
end

eps = 0.0001
a, b = -1.5, -1.0

puts "Корень бисекцией: #{bisect(a, b, eps).round(6)}"
puts "Корень Ньютона: #{newton((a+b)/2, eps).round(6)}"
puts "Корень итерациями: #{iterate((a+b)/2, eps).round(6)}"
