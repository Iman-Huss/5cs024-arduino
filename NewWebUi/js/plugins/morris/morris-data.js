// Morris.js Charts sample data for SB Admin template

$(function() {

    // Area Chart
    Morris.Area({
        element: 'morris-area-chart',
        data: [{
            period: '2015 Q1',
            Birmingham: 8432,
            Redditch: 5713,
            Walsall: 1791,
            Wolverhampton: 4988
        }, {
            period: '2015 Q2',
            Birmingham: 8322,
            Redditch: 4321,
            Walsall: 6857,
            Wolverhampton: 5124
        }, {
            period: '2015 Q3',
            Birmingham: 8492,
            Redditch: 5452,
            Walsall: 3245,
            Wolverhampton: 8764
        }, {
            period: '2015 Q4',
            Birmingham: 1234,
            Redditch: 8563,
            Walsall: 1791,
            Wolverhampton: 4988
        }, {
            period: '2016 Q1',
            Birmingham: 1232,
            Redditch: 5433,
            Walsall: 5433,
            Wolverhampton: 8653
        }, {
            period: '2016 Q2',
            Birmingham: 7653,
            Redditch: 5564,
            Walsall: 1223,
            Wolverhampton: 7642
        }, {
            period: '2016 Q3',
            Birmingham: 4532,
            Redditch: 8542,
            Walsall: 1254,
            Wolverhampton: 7645
        }, {
            period: '2016 Q4',
            Birmingham: 8432,
            Redditch: 5713,
            Walsall: 1791,
            Wolverhampton: 4988
        }, {
            period: '2017 Q1',
            Birmingham: 7656,
            Redditch: 976,
            Walsall: 1132,
            Wolverhampton: 5243
        }, {
            period: '2017 Q2',
            Birmingham: 5432,
            Redditch: 3411,
            Walsall: 1791,
            Wolverhampton: 2342
        }],
        xkey: 'period',
        ykeys: ['Birmingham', 'Redditch', 'Walsall','Wolverhampton'],
        labels: ['Birmingham', 'Redditch', 'Walsall','Wolverhampton'],
        pointSize: 2,
        hideHover: 'auto',
        resize: true
    });

    // Donut Chart
    Morris.Donut({
        element: 'morris-donut-chart',
        data: [{
            label: "Valves Open",
            value: 12
        },{
            label: "Valves Closed",
            value: 3000
        }],
        resize: true
    });

    // Line Chart
    Morris.Line({
        // ID of the element in which to draw the chart.
        element: 'morris-line-chart',
        // Chart data records -- each entry in this array corresponds to a point on
        // the chart.
        data: [{
            d: '2017-10-01',
            Flow: 802
        }, {
            d: '2017-10-02',
            Flow: 783
        }, {
            d: '2017-10-03',
            Flow: 820
        }, {
            d: '2017-10-04',
            Flow: 839
        }, {
            d: '2017-10-05',
            Flow: 792
        }, {
            d: '2017-10-06',
            Flow: 859
        }, {
            d: '2017-10-07',
            Flow: 790
        }, {
            d: '2017-10-08',
            Flow: 1680
        }, {
            d: '2017-10-09',
            Flow: 1592
        }, {
            d: '2017-10-10',
            Flow: 1420
        }, {
            d: '2017-10-11',
            Flow: 882
        }, {
            d: '2017-10-12',
            Flow: 889
        }, {
            d: '2017-10-13',
            Flow: 819
        }, {
            d: '2017-10-14',
            Flow: 849
        }, {
            d: '2017-10-15',
            Flow: 870
        }, {
            d: '2017-10-16',
            Flow: 1063
        }, {
            d: '2017-10-17',
            Flow: 1192
        }, {
            d: '2017-10-18',
            Flow: 1224
        }, {
            d: '2017-10-19',
            Flow: 1329
        }, {
            d: '2017-10-20',
            Flow: 1329
        }, {
            d: '2017-10-21',
            Flow: 1239
        }, {
            d: '2017-10-22',
            Flow: 1190
        }, {
            d: '2017-10-23',
            Flow: 1312
        }, {
            d: '2017-10-24',
            Flow: 1293
        }, {
            d: '2017-10-25',
            Flow: 1283
        }, {
            d: '2017-10-26',
            Flow: 1248
        }, {
            d: '2017-10-27',
            Flow: 1323
        }, {
            d: '2017-10-28',
            Flow: 1390
        }, {
            d: '2017-10-29',
            Flow: 1420
        }, {
            d: '2017-10-30',
            Flow: 1529
        }, {
            d: '2017-10-31',
            Flow: 1892
        }, ],
        // The name of the data record attribute that contains x-Flows.
        xkey: 'd',
        // A list of names of data record attributes that contain y-Flows.
        ykeys: ['Flow'],
        // Labels for the ykeys -- will be displayed when you hover over the
        // chart.
        labels: ['Flow'],
        // Disables line smoothing
        smooth: false,
        resize: true
    });

    // Bar Chart
    Morris.Bar({
        element: 'morris-bar-chart',
        data: [{
            device: 'Wolverhampton',
            geekbench: 136
        }, {
            device: 'Wolverhampton 3G',
            geekbench: 137
        }, {
            device: 'Wolverhampton 3GS',
            geekbench: 275
        }, {
            device: 'Wolverhampton 4',
            geekbench: 380
        }, {
            device: 'Wolverhampton 4S',
            geekbench: 655
        }, {
            device: 'Wolverhampton 5',
            geekbench: 1571
        }],
        xkey: 'device',
        ykeys: ['geekbench'],
        labels: ['Geekbench'],
        barRatio: 0.4,
        xLabelAngle: 35,
        hideHover: 'auto',
        resize: true
    });


});
