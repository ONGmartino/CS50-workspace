var map;
var markers = [];
var info = new google.maps.InfoWindow();
$(function() {
    var styles = [{
        featureType: "all",
        elementType: "labels",
        stylers: [{
            visibility: "off"
        }]
    }, {
        featureType: "road",
        elementType: "geometry",
        stylers: [{
            visibility: "off"
        }]
    }];
    var options = {
        center: {
            lat: 37.4236,
            lng: -122.1619
        },
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        maxZoom: 14,
        panControl: true,
        styles: styles,
        zoom: 13,
        zoomControl: true
    };
    var canvas = $("#map-canvas").get(0);
    map = new google.maps.Map(canvas, options);
    google.maps.event.addListenerOnce(map, "idle", configure)
});

function addMarker(place) {
    var marker = new MarkerWithLabel({
        icon: "https://maps.google.com/mapfiles/kml/pal2/icon31.png",
        labelAnchor: new google.maps.Point(22, 0),
        labelClass: "label",
        labelContent: place.place_name + ", " + place.admin_name1,
        position: new google.maps.LatLng(place.latitude, place.longitude),
        map: map
    });
    google.maps.event.addListener(marker, "click", function() {
        showInfo(marker);
        $.getJSON("articles.php", {
            geo: place.postal_code
        }).done(function(data, textStatus, jqXHR) {
            if (data.length === 0) {
                showInfo(marker, "Slow news day!")
            } else {
                var ul = "<ul>";
                var template = _.template("<li><a href='<%- link %>' target='_blank'><%- title %></a></li>");
                for (var i = 0; i < data.length; i++) {
                    ul += template({
                        link: data[i].link,
                        title: data[i].title
                    })
                }
                ul += "</ul>";
                showInfo(marker, ul)
            }
        }).fail(function(jqXHR, textStatus, errorThrown) {
            console.log(errorThrown.toString())
        })
    });
    markers.push(marker)
}

function configure() {
    google.maps.event.addListener(map, "dragend", function() {
        update()
    });
    google.maps.event.addListener(map, "zoom_changed", function() {
        update()
    });
    google.maps.event.addListener(map, "dragstart", function() {
        removeMarkers()
    });
    $("#q").typeahead({
        autoselect: true,
        highlight: false,
        minLength: 1
    }, {
        source: search,
        templates: {
            empty: "no places found yet",
            suggestion: _.template("<p>" + "<span class='place_name'><%- place_name %>, <%- admin_name1 %></span> <span class='postal_code'><%- postal_code %></span>" + "</p>")
        }
    });
    $("#q").on("typeahead:selected", function(eventObject, suggestion, name) {
        var latitude = (_.isNumber(suggestion.latitude)) ? suggestion.latitude : parseFloat(suggestion.latitude);
        var longitude = (_.isNumber(suggestion.longitude)) ? suggestion.longitude : parseFloat(suggestion.longitude);
        map.setCenter({
            lat: latitude,
            lng: longitude
        });
        update()
    });
    $("#q").focus(function(eventData) {
        hideInfo()
    });
    document.addEventListener("contextmenu", function(event) {
        event.returnValue = true;
        event.stopPropagation && event.stopPropagation();
        event.cancelBubble && event.cancelBubble()
    }, true);
    update();
    $("#q").focus()
}

function hideInfo() {
    info.close()
}

function removeMarkers() {
    for (var i = 0; i < markers.length; i++) {
        markers[i].setMap(null)
    }
    markers.length = 0
}

function search(query, cb) {
    var parameters = {
        geo: query
    };
    $.getJSON("search.php", parameters).done(function(data, textStatus, jqXHR) {
        cb(data)
    }).fail(function(jqXHR, textStatus, errorThrown) {
        console.log(errorThrown.toString());
        cb([])
    })
}

function showInfo(marker, content) {
    var div = "<div id='info'>";
    if (typeof(content) === "undefined") {
        div += "<img alt='loading' src='img/ajax-loader.gif'/>"
    } else {
        div += content
    }
    div += "</div>";
    info.setContent(div);
    info.open(map, marker)
}

function update() {
    var bounds = map.getBounds();
    var ne = bounds.getNorthEast();
    var sw = bounds.getSouthWest();
    var parameters = {
        ne: ne.lat() + "," + ne.lng(),
        q: $("#q").val(),
        sw: sw.lat() + "," + sw.lng()
    };
    $.getJSON("update.php", parameters).done(function(data, textStatus, jqXHR) {
        removeMarkers();
        for (var i = 0; i < data.length; i++) {
            addMarker(data[i])
        }
    }).fail(function(jqXHR, textStatus, errorThrown) {
        console.log(errorThrown.toString())
    })
};