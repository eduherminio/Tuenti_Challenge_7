/*
 * Author:      Eduardo Cáceres de la Calle
 *
 */


#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

const int slices_per_pizza= 8;

int main()
{
  int n_inputs;
  std::cin >> n_inputs;

  int n_people, max_slices;

  for (int input = 1; input <= n_inputs; ++input)
  {
    int n_pizzas=0, n_slices=0;
    std::cin >> n_people;

    for(int person=0; person<n_people; ++person)
    {
      std::cin >> max_slices;
      n_slices+= max_slices;
    }

    n_pizzas= n_slices / slices_per_pizza;

    if(n_slices%8)
      n_pizzas++;

  std::cout << "Case #" << input << ": " << n_pizzas << std::endl;
}

  return 0;
}
