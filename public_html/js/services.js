angular.module('smartpi.services', ['ngResource'])


.factory('$Momentary', function($resource){
    var full = location.protocol+'//'+location.hostname+(location.port ? ':'+location.port: '');
    return $resource(full+'/api/all/all/now');
})

.factory('$Linechart', function($resource){
    var full = location.protocol+'//'+location.hostname+(location.port ? ':'+location.port: '');
    return $resource(full+'/api/chart/:phase/:category/from/:startdate/to/:enddate');
})


// .factory('services', ['$http', function($http){
//   var serviceBase = 'services/'
//   var object = {};
//   var full = location.protocol+'//'+location.hostname+(location.port ? ':'+location.port: '');
//   object.getData = function(){
//     return $http.get(full+'/api/chart/123/current/from/2016-09-09%2013:58:00/to/2016-09-09%2014:02:00');
//   };
//   return object;
// }])
;
