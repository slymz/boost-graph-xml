#include <boost/test/unit_test.hpp>

#include <rapidxml_graph.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/foreach.hpp>
#include <boost/concept/requires.hpp>


// namespace this test
BOOST_AUTO_TEST_SUITE( buildme )



template<class EventPointTag>
struct TagNamePrinter
{
   void operator()(const rapidxml::xml_node<>* u, const rapidxml::xml_document<>& )
   {
      std::cout << u->name() << std::endl;
   }

   typedef EventPointTag event_filter;
};

template<class EventPointTag>
TagNamePrinter<EventPointTag> 
   print_tags(EventPointTag) { return TagNamePrinter<EventPointTag>(); }



BOOST_AUTO_TEST_CASE( buildme )
{

   char somedoc[] = {
      "<n0>"
      " <n00/>"
      " <n01>"
      "    <n010/>"
      "    <n011>"
      "       <n0110/>"
      "       <n0111/>"
      "       <n0112/>"
      "       <n0113/>"
      "    </n011>"
      "    <n012/>"
      " </n01>"
      " <n02/>"
      "</n0>"
   };

   using namespace boost;

   rapidxml::xml_document<> doc;
   doc.parse<0>( somedoc );

   typedef graph_traits< rapidxml::xml_document<> > traits;
   typedef traits::in_edge_iterator  iter;
   typedef traits::vertex_descriptor vert;
   typedef traits::edge_descriptor   edge;

    std::map< vert, default_color_type> colormap;
    breadth_first_visit( doc, doc.first_node(),
       boost::color_map( make_assoc_property_map(colormap) ).
       visitor( make_bfs_visitor( print_tags(on_discover_vertex() )) )
       );

    std::cout << "eeee?\n";

// 
// 
//    std::map< vert, vert > predecessor_map;
//    typedef std::map<vert, default_color_type>::reference colormap_ref;
//    BOOST_FOREACH( colormap_ref c, colormap ) 
//       c.second = white_color;
// 
// 
//    depth_first_visit( doc, doc.first_node(), 
//       make_dfs_visitor( 
//       record_predecessors( make_assoc_property_map(predecessor_map) , on_tree_edge() )
//       ), 
//       make_assoc_property_map(colormap)  );
// 
//    std::cout << "\nAll edges?\n";
//    typedef std::map< vert, vert >::reference predecessor_map_ref;
//    BOOST_FOREACH( predecessor_map_ref p, predecessor_map )
//       std::cout << p.first->name() << "->" << p.second->name() << "\n";
// 
//    //       doc, 
//    //       doc.first_node(), 
//    //       outputdoc, 
//    //       
//    //       )

}

BOOST_AUTO_TEST_SUITE_END()
