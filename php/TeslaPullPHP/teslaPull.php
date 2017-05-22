<?php

// ------------ Core functions ----------------

function fetchTeslaUrls($fpath) {

    $regexer = [
            1  => '/^(\/findus\/list\/stores(.*))/',
            2  => '/^(\/findus\/list\/services(.*))/',
            3  => '/^(\/findus\/list\/superchargers(.*))/',
            4  => '/^(\/findus\/list\/chargers(.*))/',
    ];

    $findus_url = 'https://www.tesla.com/findus/list';

    $findDoc = new DOMDocument();
    $urlDoc    = new DOMDocument('1.0', 'utf-8');
    @$findDoc->loadHTML(fetchHTML($findus_url));

    $links = $findDoc->getElementsByTagName('a');
    $dataNode = $urlDoc->createElement('data');

    foreach ($links as $link) {

        $href = $link->getAttribute('href');
        // echo regexer[1];
        if (preg_match('/^(\/findus\/list\/chargers(.*))/', $href))
            createElementWithText($urlDoc, $dataNode, 'url', $href);
    }

    $urlDoc->appendChild($dataNode);
    $res = $urlDoc->saveXML();
    $res = str_replace('><url>', '>' . PHP_EOL . '<url>', $res);

    file_put_contents( $fpath, $res );
    echo 'Successfully dumped urls';
}


function countChargers($fpath, $fcountpath) {

    $baseurl = 'https://www.tesla.com';

    $urlDoc = new DOMDocument();
    $urlDoc->load($fpath);

    $urls = $urlDoc->getElementsByTagName('url');
    $filestr = '';
    $total = 0;

    foreach ($urls as $url) {

        $url = $url-> nodeValue;
        $chargeHTML = new DOMDocument();
        echo 'Fetching: ' . $baseurl . $url;
        $resString = fetchHTML($baseurl . $url);
        $chargers = preg_match_all('/<address class="vcard">/', $resString);
        echo '      Found ' . $chargers . PHP_EOL;
        $total += $chargers;
        $filestr .= 'Counting: ' .  $chargers . '     Location:   '  . $url  . PHP_EOL;
    }
    $filestr .= "-----------------------" . PHP_EOL .
                "TOTAL:  " . $total . PHP_EOL .
                "-----------------------" . PHP_EOL;
    file_put_contents('c_' . $fcountpath, $filestr);
}

// ------- Utility functions ---------

function fetchHTML($url) {

    $ch = curl_init($url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);
    curl_setopt($ch, CURLOPT_AUTOREFERER,    TRUE);
    $result = curl_exec($ch);

    return $result;
}


function createElementWithText($doc, $parent, $tag, $text) {

    $textNode  = $doc ->createTextNode( $text );
    $element   = $doc ->createElement ( $tag  );
    // $element->setAttribute('style', 'color: black;');
    $element         ->appendChild   ( $textNode );
    $parent          ->appendChild   ( $element  );


}
// -------------- MAIN -----------------

//fetchTeslaUrls('charger_url.xml');                        // Fetch list of urls pointing to all the charger lists
countChargers('charger_url.xml', 'charger_count.txt');  // Each tesla location has a <adress class="vcard"> element
