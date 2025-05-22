# Данные голосования
candidates = ["Петя", "Вася", "Оля"]
votes = [
  ["Вася", "Оля", "Петя"],
  ["Вася", "Оля", "Петя"],
  ["Оля", "Петя", "Вася"],
  ["Оля", "Вася", "Петя"],
  ["Петя", "Вася", "Оля"]
]

# Метод Борда (простая сумма баллов)
borda_scores = Hash.new(0)
votes.each do |vote|
  vote.each_with_index { |c, i| borda_scores[c] += vote.size - i - 1 }
end
borda_winner = borda_scores.max_by { |k, v| v }[0]

# Метод Кондорсе (победитель в парных сравнениях)
condorcet_winner = candidates.find do |c|
  candidates.all? { |o| c == o || votes.count { |v| v.index(c) < v.index(o) } > votes.size / 2 }
end

# Вывод результатов
puts "Победитель по Борда: #{borda_winner}"
puts "Победитель по Кондорсе: #{condorcet_winner || 'нет'}"
