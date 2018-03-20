#ifndef I_BOX_HPP
#define I_BOX_HPP

#include <Utility/Vec2d.hpp>


typedef std::pair <Vec2d, Vec2d> Wall; //bottom right corner, top left corner

class Box
{
public:
	Box (Vec2d position, double largeur, double hauteur, double epaisseur);
	
	Vec2d getCenter() const;
	double getWidth() const;
	double getHeight () const;
	double getWallWidth () const;

	double getLeftlimit(bool intern = false);
	double getRightLimit(bool intern = false);
	double getTopLimit(bool intern = false);
	double getBottomLimit(bool intern = false);
	bool isPositionInside(const Vec2d&);
	bool isPositionOnWall(const Vec2d&);





private:
	Vec2d position;
	double largeur;
	double hauteur;
	double epaisseur;
/*
 * mur gauche : mur[0]
 * mur droit : mur[1]
 * mur haut : mur[2]
 * mur bas : mur[3]
 */
	Vector <Wall> mur (4);



	
}




#endif //I_BOX_HPP
