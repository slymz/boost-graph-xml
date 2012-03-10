//=======================================================================
//                 Copyright (c) 2012 S. L. Yilmaz 
//            Distributed under the MIT Software License. 
//                See accompanying file LICENSE.txt.
//=======================================================================

#ifndef BOOST_GRAPH_RAPIDXML_GRAPH_HPP_
#define BOOST_GRAPH_RAPIDXML_GRAPH_HPP_

#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/edge_list.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

#include <rapidxml/rapidxml.hpp>

namespace boost{ 


   template<class Char>
   struct graph_traits< ::rapidxml::xml_document<Char> > 
   {
   private: // some convenience typedefs
      typedef ::rapidxml::xml_document<Char> graph_t;
      typedef ::rapidxml::xml_node<Char>* nodep;

   public:
      // Graph concept
      typedef nodep vertex_descriptor;
      typedef std::pair< nodep, nodep > edge_descriptor;
      typedef directed_tag directed_category;
      typedef disallow_parallel_edge_tag edge_parallel_category;

      struct traversal_category:
         public bidirectional_graph_tag
      {};
         
      // Incidence graph concept
      typedef unsigned degree_size_type;

      class out_edge_iterator
         : public iterator_facade
         < 
         out_edge_iterator,  // my iterator
         edge_descriptor,    // value
         bidirectional_traversal_tag,  // traversal
         edge_descriptor     // reference
         >
      {
         friend boost::iterator_core_access;
         void increment() { m_sibling = m_sibling->next_sibling(); }
         void decrement() { m_sibling = m_sibling->previous_sibling(); }
         edge_descriptor dereference() const { return std::make_pair( m_sibling->parent(), m_sibling ); }
         bool equal(const out_edge_iterator& other) const { return m_sibling == other.m_sibling; }

      public:
         out_edge_iterator() : m_sibling(0) {}
         explicit out_edge_iterator( nodep parent ) : m_sibling( parent->first_node() ) {}

      private:
         nodep m_sibling;
      };


      // bidirectional graph
      class in_edge_iterator
         : public iterator_facade
         < 
         in_edge_iterator,  // my iterator
         edge_descriptor,   // value
         bidirectional_traversal_tag,  // traversal
         edge_descriptor    // reference
         >
      {
         friend boost::iterator_core_access;
         void increment() { m_sibling = 0; }
         void decrement() { m_sibling = 0; }
         edge_descriptor dereference() const { return std::make_pair( m_sibling->parent(), m_sibling ); }
         bool equal(const in_edge_iterator& other) const { return m_sibling == other.m_sibling; }

      public:
         in_edge_iterator() : m_sibling(0) {}
         explicit in_edge_iterator( nodep node ) : m_sibling( node ) {}

      private:
         nodep m_sibling;
      };

   };
   
   template< class Char >
   std::pair< 
      typename graph_traits< ::rapidxml::xml_document<Char> >::out_edge_iterator,
      typename graph_traits< ::rapidxml::xml_document<Char> >::out_edge_iterator
   >
   out_edges( 
   typename graph_traits< ::rapidxml::xml_document<Char> >::vertex_descriptor v,
   const ::rapidxml::xml_document<Char>& g 
   )
   {
      typedef typename graph_traits< ::rapidxml::xml_document<Char> >::out_edge_iterator iter;
      return std::make_pair( iter(v), iter() );
   }
   
   
   template< class Char >
   std::pair< 
      typename graph_traits< ::rapidxml::xml_document<Char> >::in_edge_iterator,
      typename graph_traits< ::rapidxml::xml_document<Char> >::in_edge_iterator
   >
   in_edges( 
   typename graph_traits< ::rapidxml::xml_document<Char> >::vertex_descriptor v,
   const ::rapidxml::xml_document<Char>& g 
   )
   {
      typedef typename graph_traits< ::rapidxml::xml_document<Char> >::in_edge_iterator iter;
      return std::make_pair( iter(v), iter() );
   }


   // source() and target() already exists for std::pair
   
 
   template< class Char >
   typename graph_traits< ::rapidxml::xml_document<Char> >::degree_size_type
      out_degree( 
      typename graph_traits< ::rapidxml::xml_document<Char> >::vertex_descriptor v,
      const ::rapidxml::xml_document<Char>& g 
      )
   {
      typename graph_traits< ::rapidxml::xml_document<Char> >::degree_size_type count = 0;
      for(v = v->first_node(); v; v = v->next_sibling() )
         count++;
      return count;
   }


   template< class Char >
   typename graph_traits< ::rapidxml::xml_document<Char> >::degree_size_type
      in_degree( 
      typename graph_traits< ::rapidxml::xml_document<Char> >::vertex_descriptor v,
      const ::rapidxml::xml_document<Char>& g 
      )
   {
      if ( v->parent()->type() == rapidxml::node_document )
         return 0;
      return 1;
   }

   template< class Char >
   typename graph_traits< ::rapidxml::xml_document<Char> >::degree_size_type
      degree( 
      typename graph_traits< ::rapidxml::xml_document<Char> >::vertex_descriptor v,
      const ::rapidxml::xml_document<Char>& g 
      )
   {
      return out_degree(v,g) + in_degree(v,g);
   }



//    template<class Char>
//    struct property_map< ::rapidxml::xml_document<Char>, vertex_color_t >
//    {
// 
//    };

}



#endif // BOOST_GRAPH_RAPIDXML_GRAPH_HPP_
