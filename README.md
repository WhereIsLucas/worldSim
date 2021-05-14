# World Sim

## Done today 14-05
* Adding the presence of predators
* Predators target preys with a noise/3
* Predators do not eat the fooditems (grass)
* The prints are done separately for preys and predators and represented with different colours
* Predators have a eatingRange of 1 (0.5 did not allow the prey to be eaten)
* When the predator eats one prey, it gains +1 in energy
* If the energy of the predator reaches +2, it replicates which gives an additionnal predator

## Todo

* Make predators faster than preys
* Allow preys to run away from predators
* Adjust a sensing range for predators (conical form rather than a circle to represent the reality better)
* Think about and opt for the best eating range
* Decide when predators can replicate (after one or two preys)
* Review the number of steps because they don't lose enough energy and come back the next day even though they haven't eaten (see with speed as well)
* Plot the evolution of predators and preys population
* Potentially find a better random because two creatures overlap when put on the sides far too often (and if it is a predator and a prey, the latter is directly eaten)
* Perhaps make the world a bit smaller (or increase steps per day) ? Because the creatures do not even have time to cover half of the plane in a day

## A few ideas :

* terrain differences
    * Water sources in some areas
* night/day
* predator/prey behaviour
* Multiple layers of food chain (herbivore/carnivore)
* Personality traits (reckless vs cautious)

## and now

* speed
* predator/prey behaviour
* terrains effect
