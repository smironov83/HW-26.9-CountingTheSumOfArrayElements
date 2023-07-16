#include <iostream>
#include <thread>
#include <chrono>

const long N = 100000000;
const int M = 10;
long long result = 0;
int *array = new int[N] {};

void CalcOutTreads(long first, long last)
{
  long long res = 0;
  for (auto i = first; i < last; ++i)
    res += array[i];
  result += res;
}

auto main() -> int
{
  system("chcp 1251");
  system("cls");
  srand((unsigned int) time(0));
  for (auto i = 0; i < N; ++i)
    array[i] = rand() % 1000000000;
  auto timeStart = std::chrono::system_clock::now();
  for (auto i = 0; i < M; ++i)
    CalcOutTreads(N / M * i, N / M * (i + 1));
  auto timeFinish = std::chrono::system_clock::now();
  auto timeSpent = std::chrono::duration_cast<std::chrono::milliseconds>
    (timeFinish - timeStart).count();
  std::cout << "Сумма всех элементов массива равна " << result << ", вычислена"
    " без использования потоков за " << timeSpent << " мс." << std::endl;
  timeStart = std::chrono::system_clock::now();
  result = 0;
  std::thread *threads = new std::thread[M] {};
  for (auto i = 0; i < M; ++i)
    threads[i] = std::thread(CalcOutTreads, N / M * i, N / M * (i + 1));  
  for (auto i = 0; i < M; ++i)
    if (threads[i].joinable())
      threads[i].join();
  timeFinish = std::chrono::system_clock::now();
  timeSpent = std::chrono::duration_cast<std::chrono::milliseconds>
    (timeFinish - timeStart).count();
  std::cout << "Сумма всех элементов массива равна " << result << ", вычислена"
    " с использованием потоков за " << timeSpent << " мс." << std::endl;
  delete[]array;
  delete[]threads;
  return 0;
}
