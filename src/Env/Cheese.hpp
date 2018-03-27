#ifndef CHEESE_HPP
#define CHEESE_HPP

#include "SimulatedEntity.hpp"


class Cheese : public SimulatedEntity
{
	public:
		/** constructor */
		Cheese(Vec2d const&);

		/** masking draw function */
		void drawOn(sf::RenderTarget&);
		
		/** get eaten you camembert */
		Quantity provideEnergy(Quantity);
		
		/** masking isDead pure virtual method */
		bool specificDead() const override;
		
	private:
		double maxSide;
};

#endif // CHEESE_HPP
