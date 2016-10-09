#include <cassert>
#include <cstdlib>
#include <iostream>

#include <fstream>

using namespace std;

const int MAX = 100;
int p[MAX];

ofstream out;

int rand_perm(int N)
{
  assert (N >= 0); assert (N < MAX);
  for (int i = 0; i < N; ++i) {
    int j = rand() % (i + 1);
    p[i] = p[j];
    p[j] = i;
  }
}

void print_rand_perm(int N)
{
  rand_perm(N);
  for (int i = 0; i < N; ++i) out << (char) ('A' + p[i]) << ",";
  out << endl;
}

void print_key(int N)
{
  out << "key:";
  for (int i = 0; i < N; ++i) out << (char) ('A' + rand()%26);
  out << endl;
}


int main()
{
  srand(time(0));
  int numRot;
  cout << "How many rotors?";
  cin >> numRot;

  out.open("ROTORS1.txt");

  out << numRot << std::endl;

  print_key(numRot);

  for (int i = 0; i < numRot; i++)
  {
   print_rand_perm(26);
  }

 out.close();

}
