/*
 * Author:      Eduardo Cáceres de la Calle
 *
 */


#include <iostream>
#include <vector>
#include <cassert>

const unsigned N_ROUNDS=        10;
const unsigned TOTAL_PINS=      10;
const unsigned MAX_ROLL_SCORE=  3*TOTAL_PINS;             // 3 ->  roll + prev. spare/strike + prev-prev strike
const unsigned MAX_TOTAL_SCORE= N_ROUNDS*MAX_ROLL_SCORE;

const int def_value=            -1;                       // To initialize int's

enum class Frame      {first_roll, second_roll};
enum class Roll_type  {regular, spare, strike};

class Roll
{
public:

  Roll()
    :n_pins(def_value), score(def_value), n_frame(def_value), frame(Frame::first_roll), roll_type(Roll_type::regular)
    {}

  int n_pins;
  int score;
  int n_frame;

  Frame frame;
  Roll_type roll_type;
};

void print_rolls  (const std::vector<Roll>& v_rolls);
void assert_rolls (const std::vector<Roll>& v_rolls);

int main()
{
  int n_games;
  std::cin >> n_games;

  for (int game = 1; game <= n_games; ++game)
  {
    int n_rolls;
    std::cin >> n_rolls;

    std::vector<Roll> v_rolls;

    for(int roll=0; roll<n_rolls; ++roll)
    {
      int n_pins;
      std::cin >> n_pins;

      Roll instance;

      instance.n_pins=  n_pins;
      instance.score=   n_pins;

      if(n_pins == TOTAL_PINS)  // strike
      {
        instance.roll_type= Roll_type::strike;
        instance.frame=     Frame::second_roll;
      }

      if(!v_rolls.empty())
      {
        Roll* last_roll= &v_rolls[roll-1];

        if(last_roll->frame == Frame::first_roll)
        {
          instance.frame=   Frame::second_roll;
          instance.n_frame= last_roll->n_frame;
        }
        else
          instance.n_frame= last_roll->n_frame+1;

        if(last_roll->roll_type == Roll_type::spare || last_roll->roll_type == Roll_type::strike)
        {
          last_roll->score+= n_pins;
        }
        else if(last_roll->frame == Frame::first_roll && (last_roll->score + n_pins) == TOTAL_PINS)  // after checking last wasn't a spare
        {
          instance.roll_type= Roll_type::spare;
        }

        if(v_rolls.size() > 1)
        {
          Roll* previous_roll= &v_rolls[roll-2];
          if(previous_roll->roll_type == Roll_type::strike)
          {
            previous_roll->score+= n_pins;
          }
        }
      }
      else  // first roll
      {
        instance.n_frame= 1;
      }

      if(v_rolls.empty() || !( v_rolls.back().n_frame == TOTAL_PINS && v_rolls.back().frame == Frame::second_roll))
      {
        v_rolls.push_back(instance);
      }
    }

    assert_rolls(v_rolls);
    // print_rolls(v_rolls);

    std::cout << "Case #" << game << ":";

    int score=0, cont=0;
    for(const auto& roll : v_rolls)
    {
      score+= roll.score;
      if(roll.frame == Frame::second_roll)
      {
        std::cout<<" "<<score;
        ++cont;
      }
    }
    std::cout<<std::endl;

    assert(score <= MAX_TOTAL_SCORE);
    assert(cont == TOTAL_PINS);
  }

  return 0;
}

void print_rolls(const std::vector<Roll>& v_roll)
{
  for(const auto& roll : v_roll)
  {
    std::cout<<roll.n_frame                     <<"\t";
    std::cout<<roll.n_pins                      <<"\t";
    std::cout<<roll.score                       <<"\t";
    std::cout<<static_cast<int>(roll.frame)     <<"\t";
    std::cout<<static_cast<int>(roll.roll_type) <<std::endl;
  }
  std::cout<<std::endl;
}

void assert_rolls(const std::vector<Roll>& v_rolls)
{
  for(int i=0; i<v_rolls.size(); ++i)
  {
    const Roll* roll= &v_rolls[i];
    assert(roll->n_frame  >   def_value);
    assert(roll->n_frame  <=  TOTAL_PINS);
    assert(roll->n_pins   >   def_value);
    assert(roll->n_pins   <=  TOTAL_PINS);
    assert(roll->score    >   def_value);
    assert(roll->score    <=  MAX_ROLL_SCORE);

    if(i!=0)
    {
      const Roll* prev_roll= &v_rolls[i-1];
      if(roll->frame == Frame::first_roll)
      {
        assert(roll->roll_type  == Roll_type::regular);
        assert(roll->n_frame    == prev_roll->n_frame+1);
        assert(prev_roll->frame == Frame::second_roll);
      }
      else
      {
        assert(prev_roll->frame == Frame::first_roll || roll->roll_type == Roll_type::strike);
      }
      if(roll->roll_type == Roll_type::spare)
      {
        assert( (roll->n_pins + prev_roll->n_pins) == TOTAL_PINS);
      }
    }
    else
    {
      assert(roll->roll_type != Roll_type::spare);
    }
  }
}
