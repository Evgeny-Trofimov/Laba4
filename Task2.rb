# Генерация случайного вещественного числа в диапазоне [min, max]
def random_double(min, max)
  rand * (max - min) + min
end

# 1. Создание массива из n случайных вещественных чисел [-100, 100]
n = 15 # n >= 10
arr = Array.new(n) { random_double(-100.0, 100.0) }
puts "Исходный массив:"
puts arr.each_slice(6).map { |slice| slice.map { |num| "%8.2f" % num }.join }.join("\n")

# 2. Количество положительных элементов
positive_count = arr.count { |num| num > 0 }
puts "\nКоличество положительных элементов: #{positive_count}"

# Сумма элементов после последнего нуля
last_zero_index = arr.rindex(0.0)
sum_after_zero = last_zero_index ? arr[(last_zero_index + 1)..-1].sum : 0.0
puts "Сумма элементов после последнего нуля: #{sum_after_zero.round(2)}"

# 3. Поиск самой длинной возрастающей последовательности
longest = []
current = []

arr.each do |num|
  if current.empty? || num > current.last
    current << num
  else
    longest = current.dup if current.size > longest.size
    current = [num]
  end
end
longest = current.dup if current.size > longest.size

puts "\nСамая длинная возрастающая последовательность (#{longest.size} элементов):"
puts longest.each_slice(6).map { |slice| slice.map { |num| "%8.2f" % num }.join }.join("\n")

# 4. Вывод массива N×6 в двух вариантах
def print_special_array(n)
  total = n * 6
  arr = (100..100 + total - 1).to_a
  
  puts "\nN = #{n}"
  puts "Вывод 1".ljust(30) + "Вывод 2"
  puts "-" * 60
  
  n.times do |i|
    # Вывод 1 - всегда прямой порядок
    line1 = arr[i*6, 6].map { |x| "%4d" % x }.join
    
    # Вывод 2 - для нечетных строк обратный порядок
    line2 = if i.even?
              arr[i*6, 6].map { |x| "%4d" % x }.join
            else
              arr[i*6, 6].reverse.map { |x| "%4d" % x }.join
            end
    
    puts "#{line1}    |    #{line2}"
  end
end

# Вывод для N=4 и N=8
print_special_array(4)
print_special_array(8)
