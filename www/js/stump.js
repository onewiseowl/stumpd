var include = function(script_source) {

  if(script_source.split('.').pop() == 'css')
  {
    var dt = 'html';
    $.ajax({
      async : false,
      url : script_source,
      type : 'GET',
      dataType : dt,
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
      success : function(data, textStatus, jqXHR) {
        eval(data);
      }
  })
  }


}

var widgets = ({
  loadWidgets : function() {
    switch(window.location.pathname) {
      case '/':
      case '/index.html':
      case '/login':
        include('/css/index.css');
        include('/js/index.js');
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
        include('/css/search.css');
        include('/js/search.js');
        widgets.search.draw();
    }
  }
});
