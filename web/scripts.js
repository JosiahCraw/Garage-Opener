$(document).ready(function () {
    $('#open').click(() => {
        $.ajax({
            url: "http://192.168.0.30/open",
            type: "GET",
            crossDomain: true,
            dataTye: "jsonp",
            success: function (response) {
                var resp = JSON.parse(response)
                console.log(resp)
            }
        });
    })
})