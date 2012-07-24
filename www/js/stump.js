function sleep(millis)
 {
  var date = new Date();
  var curDate = null;
  do { curDate = new Date(); }
  while(curDate-date < millis);
}

var include = function(script_source) {

  if(script_source.split('.').pop() == 'css')
  {
    var dt = 'html';
    $.ajax({
      async : false,
      url : script_source,
      type : 'GET',
      dataType : dt,
      cache: true,
      success : function(data, textStatus, jqXHR) {
        $('head').append(
          $('<link></link>').attr({
            rel : 'stylesheet',
            type : 'text/css',
            href : script_source
          })
        );
      }
  })
  } else {
    var dt = 'script';
    $.ajax({
      async : false,
      url : script_source,
      type : 'GET',
      dataType : dt,
      cache: true,
      success : function(data, textStatus, jqXHR) {
        try {
          eval(data);
        } catch (e) {
          if (e instanceof SyntaxError) {
            alert(e.message);
          }
        }
      }
    })
  }


}

var isFontFaceSupported = function(){

  var ua = navigator.userAgent, parsed;

  if (/*@cc_on@if(@_jscript_version>=5)!@end@*/0) 
      return true;
  if (parsed = ua.match(/Chrome\/(\d+\.\d+\.\d+\.\d+)/))
      return parsed[1] >= '4.0.249.4';
  if ((parsed = ua.match(/Safari\/(\d+\.\d+)/)) && !/iPhone/.test(ua))
      return parsed[1] >= '525.13';
  if (/Opera/.test({}.toString.call(window.opera)))
      return opera.version() >= '10.00';
  if (parsed = ua.match(/rv:(\d+\.\d+\.\d+)[^b].*Gecko\//))
      return parsed[1] >= '1.9.1';    
              
  return false;

}

if(!isFontFaceSupported)
{
  alert('@font-face is not supported by your browser, please upgrade');
}


var widgets = ({
// First, we do a feature test
  loadWidgets : function() {
    switch(window.location.pathname) {
      case '/':
      case '/index.html':
      case '/login':
        include('/css/index.css');
        include('/js/index.js');
        widgets.index.logoBox.draw();
        widgets.index.loginBox.draw();
        break;
      case '/upload':
        include('/css/upload.css');
        include('/js/upload.js');
        widgets.upload.uploadBox.draw();
        break;
      case '/home':
        include('/css/home.css');
        include('/js/home.js');
        widgets.home.draw();
        break;
        case '/search':
        include('/css/navMenu.css');
        include('/js/navMenu.js');
        include('/css/search.css');
        include('/js/search.js');
        widgets.search.draw();
        break;
        case '/tools':
        include('/css/navMenu.css');
        include('/js/navMenu.js');
        include('/css/tools.css');
        include('/js/tools.js');
        widgets.tools.draw();
    }
  }
});
