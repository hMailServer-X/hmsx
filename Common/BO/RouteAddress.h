#pragma once

namespace HM
{
   class RouteAddress : public BusinessObject<RouteAddress>
   {
   public:
	   RouteAddress();
	   virtual ~RouteAddress();

      String GetName() const {return address_; }

      long long GetRouteID() const {return route_id_;}
      void SetRouteID(long long iNewVal) {route_id_ = iNewVal; }

      String GetAddress() const {return address_; }
      void SetAddress(const String &sAddress) {address_ = sAddress; } 
   
      bool XMLStore(XNode *pNode, int iOptions);
      bool XMLLoad(XNode *pNode, int iOptions);
      bool XMLLoadSubItems(XNode *pNode, int iOptions) {return true;}

   protected:

      long long route_id_;
      String address_;
      

   };
}