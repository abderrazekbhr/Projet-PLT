// Generated by dia2code
#ifndef STATE__CARD__H
#define STATE__CARD__H


#include "NumberCard.h"
#include "TypeCard.h"

namespace state {

  /// class Card - 
  class Card {
    // Associations
    // Attributes
  private:
    int idCard;
    // Operations
  public:
    Card ();
    int  getIdCard ();
    NumberCard getNumberCard ();
    TypeCard getTypeCard ();
    ~Card ();
    // Setters and Getters
  };

};

#endif
