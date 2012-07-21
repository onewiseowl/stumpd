function split( val) {
  //return val.split( /,\s*/ );
  return val.split(/,\s*/);
}

function extractLast( term) {
    return split( term).pop();
}

var os = 0;
var oe = 0;

$.extend(widgets, {
  search : ({
    lastCommand : "",
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
        data : [{label:'myvpv01.corp.verifi.com',value:'myvpv01.corp.verifi.com'},{label:'cdrn3dbsv01.corp.verifi.com',value:'cdrn3dbsv01.corp.verifi.com'}]
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
    searchables : {
      "hosts" : [
        {
          label : 'myvpv01.corp.verifi.com',
          value : 'myvpv01.corp.verifi.com'
        },
        {
          label : 'cdrn3dbsv01.corp.verifi.com',
          value : 'cdrn3dbsv01.corp.verifi.com'
        }
      ],
      "inputs" : [
        {
          label : "/var/log/hosts/cdrn3dbsv01/cdrn_1.log",
          value : "/var/log/hosts/cdrn3dbsv01/cdrn_1.log"
        },
        {
          label : "/var/log/hosts/cdrn3dbsv02/auth.log",
          value : "/var/log/hosts/cdrn3dbsv02/auth.log"
        }
      ]
    },
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
            // determine if cursor is between two quotes
            if(request.term.substring(request.term.length - 3,request.term.length) == '", ')
            {              
              var terms = request.term.split(/"/);
              if(terms[terms.length - 2].match(/,/) == ',')
              {
                var sub_terms = terms[terms.length - 2].split(/,/);
                response( $.ui.autocomplete.filter(
                  widgets.search.searchables[widgets.search.lastCommand], sub_terms.pop() ) );
              } else {
                response( $.ui.autocomplete.filter(
                  widgets.search.searchables[widgets.search.lastCommand], terms[terms.length - 2] ) );
              }
            } else {
            response( $.ui.autocomplete.filter(
	      widgets.search.searchCommands, extractLast( request.term ) ) );
            }
          },
          focus: function() {
            // prevent value inserted on focus
            return false;
          },
          select: function( event, ui ) {
            
            if($('input#_queryInput')[0].value.substring($('input#_queryInput')[0].selectionStart, $('input#_queryInput')[0].selectionStart + 1) == '"')
            {
              //find previous comma, or quotation mark
              var delim;
              var position = $('input#_queryInput')[0].selectionStart;
              while(delim != ',' && delim != '"' && position > 0)
              {
                delim = $('input#_queryInput')[0].value.substring(--position, position+1) ;
              }
              //alert("Found delimiter " + delim + " at position: " + position + " and search term is " + ui.item.value);

              $('input#_queryInput')[0].value = $('input#_queryInput')[0].value.substring(0, position+1) + ui.item.value + $('input#_queryInput')[0].value.substring($('input#_queryInput')[0].selectionStart, $('input#_queryInput')[0].value.length);

              //var terms = split( this.value );
              //terms.pop();
              //terms.push( ui.item.value );
              //terms.push( '' );
              //this.value = terms.join( ',' );

            } else {
              var terms = split( this.value );
              widgets.search.lastCommand = ui.item.label;
              console.log("widgets.search.lastCommand: " + widgets.search.lastCommand);
              terms.pop();
              terms.push( ui.item.value + '""' );
              terms.push( '' );
              this.value = terms.join( ', ' );
              $('input#_queryInput')[0].setSelectionRange(
                 this.value.length - 3,
                 this.value.length - 3
               );
             }
            //widgets.search.menu.getAutoComplete($('input#_queryInput')[0],ui.item.label);
            //alert(ui.item.data);
            //$('input#_queryInput').autocomplete( "option", "source", function(request, response) {
            //     console.log($.ui.autocomplete.filter(
            //      widgets.search.searchCommands, extractLast( request.term, /"*",/ ) ));
            //    response( $.ui.autocomplete.filter(
            //      widgets.search.searchHosts, extractLast( request.term, /"*",/ ) ) );
            //  }
            //);
            /*
            $('input#_queryInput').autocomplete( "option", "select", function(event, ui) {
               var terms = split( this.value );
               terms.pop();
               terms.push( ui.item.value);
               terms.push( '' );
               this.value = terms.join( ", " );
              }
            );
            */
            return false;
          }
        });              
      });
    }
  })
});
