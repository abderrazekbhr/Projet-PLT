// Generated by dia2code
#ifndef STATE__CARD__H
#define STATE__CARD__H


#include "TypeCard.h"
#include "NumberCard.h"

namespace state {

  /// class Card - 
  class Card {
    // Associations
    // Attributes
  private:
    int idCard;
    TypeCard typeOfCard;
    NumberCard numberOfCard;
    static int nbCardInstrance;
    // Operations
  public:
    Card (NumberCard number, TypeCard type);
    int  getIdCard ();
    NumberCard getNumberCard ();
    TypeCard getTypeCard ();
    ~Card ();
    // Setters and Getters
  };

};

#endif
