#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Animal.hpp"


class Mouse : public Animal
{
	public:
		/** Default constructor */
		Mouse();

		/**	masked draw function
		 *	@param SFML window
		 */
		void drawOn(sf::RenderTarget&);
	private:
		double mouseSize;
};

#endif // MOUSE_HPP
