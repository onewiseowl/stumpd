function split( val ) {
  return val.split( /,\s*/ );
}

function extractLast( term ) {
  return split( term ).pop();
}

var os = 0;
var oe = 0;

$.extend(widgets, {
  search : ({
    searchCommands : [
      {
        label : 'dateFrom',
        value : 'dateFrom:'
      },
      {
        label : 'dateTo',
        value : 'dateTo:'
      },
      {
        label : 'hosts',
        value : 'hosts:',
        data : 'myvpv01.corp.verifi.com,cdrn3dbsv01.corp.verifi.com'
      },
      {
        label : 'inputs',
        value : 'inputs:'
      },
      {
        label : 'query',
        value : 'query:'
      },
      {
        label : 'sortBy',
        value : 'sortBy:'
      }
    ],
    menu : ({
      sources : [{}],
      getSources : function() {
        $.ajax({
          url : "/api",
          type : "GET",
          data : {
            action : "getSources"
          },
          success : function(data, textStatus, jqXHR) {
            this.sources = (data);
            //alert(data);
          }
        });
      },
      draw : function() {
        widgets.search.menu.getSources();
        $('body').append(
          $('<br />'),
          $('<input></input>').attr({
            id : '_queryInput',
            name : '_queryInput',
            class : '_queryInput'
          })
        );
      },
      getAutoComplete : function(obj, str)
      {
        $.grep(widgets.search.searchCommands, function(item){
          if (item.label == str)
          {
            alert(item.data);
          }
        });
      }
    }),
    draw : function() {
      widgets.navMenu.draw();
      widgets.search.menu.draw();
      $(document).ready(function() {
        $('input#_queryInput').autocomplete({
          delay: 50,
          source: function( request, response ) {
            response( $.ui.autocomplete.filter(
	      widgets.search.searchCommands, extractLast( request.term ) ) );
          },
          focus: function() {
            // prevent value inserted on focus
            return false;
          },
          select: function( event, ui ) {
            var terms = split( this.value );
            terms.pop();
            terms.push( ui.item.value + '""' );
            terms.push( '' );
            this.value = terms.join( ", " );
            $('input#_queryInput')[0].setSelectionRange(
               this.value.length - 3,
               this.value.length - 3
             );
            widgets.search.menu.getAutoComplete($('input#_queryInput')[0],ui.item.label);
            return false;
          }
        });              
      });
    }
  })
});
