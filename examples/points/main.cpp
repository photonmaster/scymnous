#include "server/app.hpp"


using namespace scymnus;


///In this example a simple web service will be created for manipulating a collection of 3D points
///Firsly a model for our 3D point must be created:

using PointModel = model<
    field<"id", std::optional<int>>, //server sets this
    field<"x", int>,
    field<"y", int>,
    field<"z", int>
    >;


/**
PointModel is a type with 4 fields. Each field has  name and a type.
This is mandatory because support for basic reflection is missing from c++ (as of c++ 20)
This means that we can't use something like the following:

struct PointModel {
    std::optional<int> id;
    int x;
    int y;
    int z;
};

to support
encoding and decoding to/from json and
swagger documentation

for our model
**/





///the follwing map is our data source:

std::map<int, PointModel> points{};

/// The endpoints that will be exposed by our service,  will operate
///on the above map.
///(We are using a map bacause each point will have a unique id, that is the key of our map)



///lets now define our main function




int main(){
    /// scymnus::app is a singleton. we are taking a reference to singeton's instance, named app
    /// that we will be using in the rest of the code
    auto& app = scymnus::app::instance();


    ///for creating 3D point we will define first a POST endpoint.
    /// clients will be calling the follwing API
    /// POST /points
    /// for creating points.
    /// Whenever a point is created it will be added in our map of points


    app.route([](body_param<"body", PointModel> body, context& ctx) -> response_for<http_method::POST, "/points">
           {
               auto p = body.get();
               p.get<"id">() = points.size(); //code is not thread safe

               points[points.size()] = p;
               return ctx.write(status<200>, p);
              })
        .summary("Create a point")
        .description("Create a point resource. The id will be returned in the response")
        .tag("points");



    /// we are using the route method of our app instance to route our endpoint
    /// route method takes a callable as argument (a lambda).
    /// a context parameter is always needed a argument of our callable.
    /// a context is our handle to the http request and http response
    /// Clients that are calling the POST /points API must send a point model (in JSON format) in the body of their request.
    /// For this reason we are adding the parameter: body_param<"body", PointModel> body
    /// as the first argument of our callable
    ///
    /// the class body_param<> is used only to support swagger documentation for a web service
    ///
    /// the object that is returned by our callable is of type:
    ///
    /// response_for<http_method::POST, "/points">
    ///
    /// the template parameters of the response_for class type
    /// are used for specifying the http method of our endpoint and the endpoint itself
    ///
    ///
    /// Finally we are using the summary(), description() and tag() methods for better documenting our webservice:

    ///.summary("Create a point")
    ///.description("Create a point resource. The id will be returned in the response")
    ///.tag("points");



    ///Let's now add an endpoint for retrieving points given their id:

    app.route([](path_param<"id", int> id, context& ctx)
               -> response_for<http_method::GET, "/points/{id}">
           {
               if (points.count(id.get()))
                   return ctx.write(status<200>, points[id.get()]);
               else
                   return ctx.write_as<http_content_type::JSON>(status<404>, std::string{"Point not found"});

              })
        .summary("get a point")
        .description("retrieve a point by id")
        .tag("points");

    /// For our get endpoint we are using a path_param<> argument.
    /// the name of the path param: "id" must be present in the endpoint of the response_for return type:
    /// response_for<http_method::GET, "/points/{id}">


    ///We will add now an endpoint for deleting a point given point's id
    ///
    ///

    app.route([](path_param<"id", int> id, context& ctx)
                  -> response_for<http_method::DELETE, "/points/{id}">
              {
                  auto count = points.erase(id.get());

                  if (count)
                      return ctx.write(status<204>);
                  else
                      return ctx.write_as<http_content_type::JSON>(status<404>, std::string{"Point not found"});

              })
        .summary("remove a point")
        .description("remove a point by id")
        .tag("points");

    ///The last endpoint for this endpoint will return all the points in our map
    ///
    app.route([](context& ctx)
                  -> response_for<http_method::GET, "/points">
              {
                  std::vector<PointModel> data;

                  for(auto element : points)
                      data.push_back(element.second);

                  return ctx.write(status<200>,data);

              })
        .summary("get all points")
        .description("get a list of avaliable points")
        .tag("points");



    /// Finally we are starting the webservice
    /// swagger is accessible here: http://10.0.2.15:9090/api-doc


    app.listen();
    app.run();
}

