# Структура для хранения информации о кандидате
class Candidate
  attr_accessor :name, :borda_score, :condorcet_wins

  def initialize(name)
    @name = name
    @borda_score = 0
    @condorcet_wins = {} # Хэш для хранения количества побед над другими кандидатами
  end
end

# Функция для подсчета очков по методу Борда
def calculate_borda_scores(candidates, votes)
  n = candidates.size
  
  # Обнуляем все очки
  candidates.each { |c| c.borda_score = 0 }
  
  # Для каждого голоса
  votes.each do |vote|
    # Для каждой позиции в голосе
    vote.each_with_index do |candidate_name, pos|
      # Находим кандидата и добавляем ему очки
      candidates.each do |c|
        if c.name == candidate_name
          c.borda_score += (n - pos - 1)
          break
        end
      end
    end
  end
end

# Функция для определения победителя по методу Борда
def find_borda_winner(candidates)
  max_score = -1
  winner = ""
  
  candidates.each do |c|
    if c.borda_score > max_score
      max_score = c.borda_score
      winner = c.name
    end
  end
  
  winner
end

# Функция для парных сравнений по методу Кондорсе
def calculate_condorcet_wins(candidates, votes)
  # Инициализация счетчиков побед
  candidates.each do |c1|
    candidates.each do |c2|
      if c1.name != c2.name
        c1.condorcet_wins[c2.name] = 0
      end
    end
  end
  
  # Для каждого голоса
  votes.each do |vote|
    # Сравниваем каждую пару кандидатов
    (0...vote.size).each do |i|
      (i+1...vote.size).each do |j|
        first = vote[i]
        second = vote[j]
        
        # Увеличиваем счетчик побед для кандидата, который выше в списке
        candidates.each do |c|
          if c.name == first
            c.condorcet_wins[second] += 1
          end
        end
      end
    end
  end
end

# Функция для определения победителя по методу Кондорсе
def find_condorcet_winner(candidates)
  return "Нет победителя по Кондорсе" if candidates.empty?

  # Находим количество избирателей
  total_voters = 0
  candidates.each do |c|
    c.condorcet_wins.each_value do |wins|
      total_voters = [total_voters, wins].max
    end
  end
  
  # Ищем кандидата, который побеждает всех остальных
  candidates.each do |c|
    is_winner = true
    
    candidates.each do |opponent|
      if c.name != opponent.name
        # Если есть кандидат, которого наш кандидат не побеждает
        if c.condorcet_wins[opponent.name] <= total_voters / 2
          is_winner = false
          break
        end
      end
    end
    
    return c.name if is_winner
  end
  
  "Нет победителя по Кондорсе"
end

# Основная программа
puts "Введите количество кандидатов: "
n = gets.chomp.to_i
puts "Введите количество избирателей: "
k = gets.chomp.to_i

candidates = []
puts "Введите имена кандидатов (по одному в строке):"
n.times do
  name = gets.chomp
  candidates << Candidate.new(name)
end

votes = []
puts "Введите голоса избирателей (каждый голос -
