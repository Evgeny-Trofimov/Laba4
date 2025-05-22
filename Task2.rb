# Генерация случайного числа
def rand_num(min, max)
  rand * (max - min) + min
end

# 1. Создаем массив из 15 чисел [-100, 100]
nums = Array.new(15) { rand_num(-100, 100) }
puts "Массив: #{nums.map { |n| '%.2f' % n }.join(', ')}"

# 2. Считаем положительные числа и сумму после последнего нуля
positives = nums.count { |n| n > 0 }
last_zero = nums.rindex(0.0)
sum_after_zero = last_zero ? nums[last_zero+1..-1].sum : 0

puts "Положительных: #{positives}"
puts "Сумма после нуля: #{sum_after_zero.round(2)}"

# 3. Находим самую длинную возрастающую последовательность
longest = []
current = []

nums.each do |n|
  current = (current.empty? || n > current.last) ? current + [n] : [n]
  longest = current if current.size > longest.size
end

puts "Самая длинная последовательность: #{longest.map { |n| '%.2f' % n }.join(', ')}"

# 4. Выводим массив 4×6 и 8×6
def print_array(n)
  arr = (100..100+n*6-1).to_a
  puts "\nN=#{n}:"
  n.times do |i|
    part = arr[i*6, 6]
    puts "#{part.map { |x| '%4d' % x }.join} | #{i.odd? ? part.reverse.map { |x| '%4d' % x }.join : part.map { |x| '%4d' % x }.join}"
  end
end

print_array(4)
print_array(8)
