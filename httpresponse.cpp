#include "httpresponse.h"
/*
    int datalen;
    map<string, string> headers;
    string version;
    int status;
    string reason;
    bool headflag; //写data之前数据有没有写?
    const MySocket* skfd
    static map<string, string> MIME_TYPE
*/

map<string,string> HttpResponse::MIME_TYPE(HttpResponse::mime_init());


    
int HttpResponse::addHeader(string  key, string val){
    if(headers.find(key) == headers.end()){
        return -1;
    }
    headers.insert(pair<string, string>(key,val));
    return 0;
};

int HttpResponse::setHeader(string  key, string val){
    headers.insert(pair<string, string>(key,val));
    return 0;
};

int HttpResponse::setStatus(int arg_status=200){
    status = arg_status;
    switch(status/100){
        case 1:
            reason = "Connect";
        case 2:
            reason = "OK";
        case 3:
            reason = "move";
        case 4:
            reason = "clienterror";
        default:
            reason = "servererror";
    }
    return 0;
};

int HttpResponse::setVersion(string arg_version="HTTP/0.9"){
    version = arg_version ;
    return 0;
};

int HttpResponse::setDataLen(long arg_dlen){
    datalen = arg_dlen;
    char str_len[15];
    sprintf(str_len,"%ld",datalen);
    headers.insert(pair<string, string>("Content-Length",string(str_len)));
    return 0;
};

int HttpResponse::writeData(char* buffer, int len){
    if(headflag){
        skfd->mywrite(buffer, len);
    }else{
        writeHeader();
        skfd->mywrite(buffer, len);
    }
};

int HttpResponse::writeData(string & buffer){
    if(headflag){
        skfd->mywrite(buffer);
    }else{
        writeHeader();
        //cout<<"write head finished"<<endl;
        skfd->mywrite(buffer);
    }
    //cout<<"write data finish"<<endl;
}

int HttpResponse::writeHeader(){
    //char tmp_buf[5];
    //sprintf(tmp_buf,"%d",status);
    //string status_str(tmp_buf);
    string status_str="200";
    string tag;
    tag.append(version);
    tag.append(" ");
    tag.append(status_str);
    tag.append(" ");
    tag.append(reason);
    tag.append("\r\n");

    skfd->mywrite(tag);

    string wbuff;
    for(map<string, string>::iterator it=headers.begin(); it!=headers.end(); ++it){
        wbuff = wbuff + it->first;
        wbuff = wbuff + ":";
        wbuff = wbuff + it->second;
        wbuff = wbuff + "\r\n";
        //cout<<"write head:"<<wbuff;
        skfd->mywrite(wbuff);
        wbuff.clear();
    }
    string crlf = "\r\n";
    skfd->mywrite(crlf); 
    //cout<<"int writeheader finished"<<endl;
    headflag = true;
    return 0;
};

int HttpResponse::finish(){};

HttpResponse::HttpResponse(MySocket * arg_skfd):skfd(arg_skfd){
    headflag = 0;
    status = 200;
    reason = "OK";
    version = "HTTP/1.0";
}


HttpResponse::~HttpResponse(){
    headers.clear();
    cout<<"clear"<<endl;
};


/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    string data = "this is data";
    int fd = open("./fileout",O_RDWR|O_TRUNC);
    MySocket msk(fd);
    HttpResponse res(&msk);
    res.setHeader("a","b");
    res.setDataLen(29);
    res.writeHeader();
    res.writeData(data);

    return 0;

}*/

map<string,string> HttpResponse::mime_init(){
    map<string,string> tmp;
    tmp[".3gp"] = "video/3gpp";
    tmp[".aab"] = "application/x-authoware-bin";
    tmp[".aam"] = "application/x-authoware-map";
    tmp[".aas"] = "application/x-authoware-seg";
    tmp[".ai"] = "application/postscript";
    tmp[".aif"] = "audio/x-aiff";
    tmp[".aifc"] = "audio/x-aiff";
    tmp[".aiff"] = "audio/x-aiff";
    tmp[".als"] = "audio/X-Alpha5";
    tmp[".amc"] = "application/x-mpeg";
    tmp[".ani"] = "application/octet-stream";
    tmp[".asc"] = "text/plain";
    tmp[".asd"] = "application/astound";
    tmp[".asf"] = "video/x-ms-asf";
    tmp[".asn"] = "application/astound";
    tmp[".asp"] = "application/x-asap";
    tmp[".asx"] = "video/x-ms-asf";
    tmp[".au"] = "audio/basic";
    tmp[".avb"] = "application/octet-stream";
    tmp[".avi"] = "video/x-msvideo";
    tmp[".awb"] = "audio/amr-wb";
    tmp[".bcpio"] = "application/x-bcpio";
    tmp[".bin"] = "application/octet-stream";
    tmp[".bld"] = "application/bld";
    tmp[".bld2"] = "application/bld2";
    tmp[".bmp"] = "application/x-MS-bmp";
    tmp[".bpk"] = "application/octet-stream";
    tmp[".bz2"] = "application/x-bzip2";
    tmp[".cal"] = "image/x-cals";
    tmp[".ccn"] = "application/x-cnc";
    tmp[".cco"] = "application/x-cocoa";
    tmp[".cdf"] = "application/x-netcdf";
    tmp[".cgi"] = "magnus-internal/cgi";
    tmp[".chat"] = "application/x-chat";
    tmp[".class"] = "application/octet-stream";
    tmp[".clp"] = "application/x-msclip";
    tmp[".cmx"] = "application/x-cmx";
    tmp[".co"] = "application/x-cult3d-object";
    tmp[".cod"] = "image/cis-cod";
    tmp[".cpio"] = "application/x-cpio";
    tmp[".cpt"] = "application/mac-compactpro";
    tmp[".crd"] = "application/x-mscardfile";
    tmp[".csh"] = "application/x-csh";
    tmp[".csm"] = "chemical/x-csml";
    tmp[".csml"] = "chemical/x-csml";
    tmp[".css"] = "text/css";
    tmp[".cur"] = "application/octet-stream";
    tmp[".dcm"] = "x-lml/x-evm";
    tmp[".dcr"] = "application/x-director";
    tmp[".dcx"] = "image/x-dcx";
    tmp[".dhtml"] = "text/html";
    tmp[".dir"] = "application/x-director";
    tmp[".dll"] = "application/octet-stream";
    tmp[".dmg"] = "application/octet-stream";
    tmp[".dms"] = "application/octet-stream";
    tmp[".doc"] = "application/msword";
    tmp[".dot"] = "application/x-dot";
    tmp[".dvi"] = "application/x-dvi";
    tmp[".dwf"] = "drawing/x-dwf";
    tmp[".dwg"] = "application/x-autocad";
    tmp[".dxf"] = "application/x-autocad";
    tmp[".dxr"] = "application/x-director";
    tmp[".ebk"] = "application/x-expandedbook";
    tmp[".emb"] = "chemical/x-embl-dl-nucleotide";
    tmp[".embl"] = "chemical/x-embl-dl-nucleotide";
    tmp[".eps"] = "application/postscript";
    tmp[".eri"] = "image/x-eri";
    tmp[".es"] = "audio/echospeech";
    tmp[".esl"] = "audio/echospeech";
    tmp[".etc"] = "application/x-earthtime";
    tmp[".etx"] = "text/x-setext";
    tmp[".evm"] = "x-lml/x-evm";
    tmp[".evy"] = "application/x-envoy";
    tmp[".exe"] = "application/octet-stream";
    tmp[".fh4"] = "image/x-freehand";
    tmp[".fh5"] = "image/x-freehand";
    tmp[".fhc"] = "image/x-freehand";
    tmp[".fif"] = "image/fif";
    tmp[".fm"] = "application/x-maker";
    tmp[".fpx"] = "image/x-fpx";
    tmp[".fvi"] = "video/isivideo";
    tmp[".gau"] = "chemical/x-gaussian-input";
    tmp[".gca"] = "application/x-gca-compressed";
    tmp[".gdb"] = "x-lml/x-gdb";
    tmp[".gif"] = "image/gif";
    tmp[".gps"] = "application/x-gps";
    tmp[".gtar"] = "application/x-gtar";
    tmp[".gz"] = "application/x-gzip";
    tmp[".hdf"] = "application/x-hdf";
    tmp[".hdm"] = "text/x-hdml";
    tmp[".hdml"] = "text/x-hdml";
    tmp[".hlp"] = "application/winhlp";
    tmp[".hqx"] = "application/mac-binhex40";
    tmp[".htm"] = "text/html";
    tmp[".html"] = "text/html";
    tmp[".hts"] = "text/html";
    tmp[".ice"] = "x-conference/x-cooltalk";
    tmp[".ico"] = "application/octet-stream";
    tmp[".ief"] = "image/ief";
    tmp[".ifm"] = "image/gif";
    tmp[".ifs"] = "image/ifs";
    tmp[".imy"] = "audio/melody";
    tmp[".ins"] = "application/x-NET-Install";
    tmp[".ips"] = "application/x-ipscript";
    tmp[".ipx"] = "application/x-ipix";
    tmp[".it"] = "audio/x-mod";
    tmp[".itz"] = "audio/x-mod";
    tmp[".ivr"] = "i-world/i-vrml";
    tmp[".j2k"] = "image/j2k";
    tmp[".jad"] = "text/vnd.sun.j2me.app-descriptor";
    tmp[".jam"] = "application/x-jam";
    tmp[".jar"] = "application/java-archive";
    tmp[".jnlp"] = "application/x-java-jnlp-file";
    tmp[".jpe"] = "image/jpeg";
    tmp[".jpeg"] = "image/jpeg";
    tmp[".jpg"] = "image/jpeg";
    tmp[".jpz"] = "image/jpeg";
    tmp[".js"] = "application/x-javascript";
    tmp[".jwc"] = "application/jwc";
    tmp[".kjx"] = "application/x-kjx";
    tmp[".lak"] = "x-lml/x-lak";
    tmp[".latex"] = "application/x-latex";
    tmp[".lcc"] = "application/fastman";
    tmp[".lcl"] = "application/x-digitalloca";
    tmp[".lcr"] = "application/x-digitalloca";
    tmp[".lgh"] = "application/lgh";
    tmp[".lha"] = "application/octet-stream";
    tmp[".lml"] = "x-lml/x-lml";
    tmp[".lmlpack"] = "x-lml/x-lmlpack";
    tmp[".lsf"] = "video/x-ms-asf";
    tmp[".lsx"] = "video/x-ms-asf";
    tmp[".lzh"] = "application/x-lzh";
    tmp[".m13"] = "application/x-msmediaview";
    tmp[".m14"] = "application/x-msmediaview";
    tmp[".m15"] = "audio/x-mod";
    tmp[".m3u"] = "audio/x-mpegurl";
    tmp[".m3url"] = "audio/x-mpegurl";
    tmp[".ma1"] = "audio/ma1";
    tmp[".ma2"] = "audio/ma2";
    tmp[".ma3"] = "audio/ma3";
    tmp[".ma5"] = "audio/ma5";
    tmp[".man"] = "application/x-troff-man";
    tmp[".map"] = "magnus-internal/imagemap";
    tmp[".mbd"] = "application/mbedlet";
    tmp[".mct"] = "application/x-mascot";
    tmp[".mdb"] = "application/x-msaccess";
    tmp[".mdz"] = "audio/x-mod";
    tmp[".me"] = "application/x-troff-me";
    tmp[".mel"] = "text/x-vmel";
    tmp[".mi"] = "application/x-mif";
    tmp[".mid"] = "audio/midi";
    tmp[".midi"] = "audio/midi";
    tmp[".mif"] = "application/x-mif";
    tmp[".mil"] = "image/x-cals";
    tmp[".mio"] = "audio/x-mio";
    tmp[".mmf"] = "application/x-skt-lbs";
    tmp[".mng"] = "video/x-mng";
    tmp[".mny"] = "application/x-msmoney";
    tmp[".moc"] = "application/x-mocha";
    tmp[".mocha"] = "application/x-mocha";
    tmp[".mod"] = "audio/x-mod";
    tmp[".mof"] = "application/x-yumekara";
    tmp[".mol"] = "chemical/x-mdl-molfile";
    tmp[".mop"] = "chemical/x-mopac-input";
    tmp[".mov"] = "video/quicktime";
    tmp[".movie"] = "video/x-sgi-movie";
    tmp[".mp2"] = "audio/x-mpeg";
    tmp[".mp3"] = "audio/x-mpeg";
    tmp[".mp4"] = "video/mp4";
    tmp[".mpc"] = "application/vnd.mpohun.certificate";
    tmp[".mpe"] = "video/mpeg";
    tmp[".mpeg"] = "video/mpeg";
    tmp[".mpg"] = "video/mpeg";
    tmp[".mpg4"] = "video/mp4";
    tmp[".mpga"] = "audio/mpeg";
    tmp[".mpn"] = "application/vnd.mophun.application";
    tmp[".mpp"] = "application/vnd.ms-project";
    tmp[".mps"] = "application/x-mapserver";
    tmp[".mrl"] = "text/x-mrml";
    tmp[".mrm"] = "application/x-mrm";
    tmp[".ms"] = "application/x-troff-ms";
    tmp[".mts"] = "application/metastream";
    tmp[".mtx"] = "application/metastream";
    tmp[".mtz"] = "application/metastream";
    tmp[".mzv"] = "application/metastream";
    tmp[".nar"] = "application/zip";
    tmp[".nbmp"] = "image/nbmp";
    tmp[".nc"] = "application/x-netcdf";
    tmp[".ndb"] = "x-lml/x-ndb";
    tmp[".ndwn"] = "application/ndwn";
    tmp[".nif"] = "application/x-nif";
    tmp[".nmz"] = "application/x-scream";
    tmp[".nokia"] = "op-logo image/vnd.nok-oplogo-color";
    tmp[".npx"] = "application/x-netfpx";
    tmp[".nsnd"] = "audio/nsnd";
    tmp[".nva"] = "application/x-neva1";
    tmp[".oda"] = "application/oda";
    tmp[".oom"] = "application/x-AtlasMate-Plugin";
    tmp[".pac"] = "audio/x-pac";
    tmp[".pae"] = "audio/x-epac";
    tmp[".pan"] = "application/x-pan";
    tmp[".pbm"] = "image/x-portable-bitmap";
    tmp[".pcx"] = "image/x-pcx";
    tmp[".pda"] = "image/x-pda";
    tmp[".pdb"] = "chemical/x-pdb";
    tmp[".pdf"] = "application/pdf";
    tmp[".pfr"] = "application/font-tdpfr";
    tmp[".pgm"] = "image/x-portable-graymap";
    tmp[".pict"] = "image/x-pict";
    tmp[".pm"] = "application/x-perl";
    tmp[".pmd"] = "application/x-pmd";
    tmp[".png"] = "image/png";
    tmp[".pnm"] = "image/x-portable-anymap";
    tmp[".pnz"] = "image/png";
    tmp[".pot"] = "application/vnd.ms-powerpoint";
    tmp[".ppm"] = "image/x-portable-pixmap";
    tmp[".pps"] = "application/vnd.ms-powerpoint";
    tmp[".ppt"] = "application/vnd.ms-powerpoint";
    tmp[".pqf"] = "application/x-cprplayer";
    tmp[".pqi"] = "application/cprplayer";
    tmp[".prc"] = "application/x-prc";
    tmp[".proxy"] = "application/x-ns-proxy-autoconfig";
    tmp[".ps"] = "application/postscript";
    tmp[".ptlk"] = "application/listenup";
    tmp[".pub"] = "application/x-mspublisher";
    tmp[".pvx"] = "video/x-pv-pvx";
    tmp[".qcp"] = "audio/vnd.qcelp";
    tmp[".qt"] = "video/quicktime";
    tmp[".qti"] = "image/x-quicktime";
    tmp[".qtif"] = "image/x-quicktime";
    tmp[".r3t"] = "text/vnd.rn-realtext3d";
    tmp[".ra"] = "audio/x-pn-realaudio";
    tmp[".ram"] = "audio/x-pn-realaudio";
    tmp[".rar"] = "application/x-rar-compressed";
    tmp[".ras"] = "image/x-cmu-raster";
    tmp[".rdf"] = "application/rdf+xml";
    tmp[".rf"] = "image/vnd.rn-realflash";
    tmp[".rgb"] = "image/x-rgb";
    tmp[".rlf"] = "application/x-richlink";
    tmp[".rm"] = "audio/x-pn-realaudio";
    tmp[".rmf"] = "audio/x-rmf";
    tmp[".rmm"] = "audio/x-pn-realaudio";
    tmp[".rmvb"] = "audio/x-pn-realaudio";
    tmp[".rnx"] = "application/vnd.rn-realplayer";
    tmp[".roff"] = "application/x-troff";
    tmp[".rp"] = "image/vnd.rn-realpix";
    tmp[".rpm"] = "audio/x-pn-realaudio-plugin";
    tmp[".rt"] = "text/vnd.rn-realtext";
    tmp[".rte"] = "x-lml/x-gps";
    tmp[".rtf"] = "application/rtf";
    tmp[".rtg"] = "application/metastream";
    tmp[".rtx"] = "text/richtext";
    tmp[".rv"] = "video/vnd.rn-realvideo";
    tmp[".rwc"] = "application/x-rogerwilco";
    tmp[".s3m"] = "audio/x-mod";
    tmp[".s3z"] = "audio/x-mod";
    tmp[".sca"] = "application/x-supercard";
    tmp[".scd"] = "application/x-msschedule";
    tmp[".sdf"] = "application/e-score";
    tmp[".sea"] = "application/x-stuffit";
    tmp[".sgm"] = "text/x-sgml";
    tmp[".sgml"] = "text/x-sgml";
    tmp[".sh"] = "application/x-sh";
    tmp[".shar"] = "application/x-shar";
    tmp[".shtml"] = "magnus-internal/parsed-html";
    tmp[".shw"] = "application/presentations";
    tmp[".si6"] = "image/si6";
    tmp[".si7"] = "image/vnd.stiwap.sis";
    tmp[".si9"] = "image/vnd.lgtwap.sis";
    tmp[".sis"] = "application/vnd.symbian.install";
    tmp[".sit"] = "application/x-stuffit";
    tmp[".skd"] = "application/x-Koan";
    tmp[".skm"] = "application/x-Koan";
    tmp[".skp"] = "application/x-Koan";
    tmp[".skt"] = "application/x-Koan";
    tmp[".slc"] = "application/x-salsa";
    tmp[".smd"] = "audio/x-smd";
    tmp[".smi"] = "application/smil";
    tmp[".smil"] = "application/smil";
    tmp[".smp"] = "application/studiom";
    tmp[".smz"] = "audio/x-smd";
    tmp[".snd"] = "audio/basic";
    tmp[".spc"] = "text/x-speech";
    tmp[".spl"] = "application/futuresplash";
    tmp[".spr"] = "application/x-sprite";
    tmp[".sprite"] = "application/x-sprite";
    tmp[".spt"] = "application/x-spt";
    tmp[".src"] = "application/x-wais-source";
    tmp[".stk"] = "application/hyperstudio";
    tmp[".stm"] = "audio/x-mod";
    tmp[".sv4cpio"] = "application/x-sv4cpio";
    tmp[".sv4crc"] = "application/x-sv4crc";
    tmp[".svf"] = "image/vnd";
    tmp[".svg"] = "image/svg-xml";
    tmp[".svh"] = "image/svh";
    tmp[".svr"] = "x-world/x-svr";
    tmp[".swf"] = "application/x-shockwave-flash";
    tmp[".swfl"] = "application/x-shockwave-flash";
    tmp[".t"] = "application/x-troff";
    tmp[".tad"] = "application/octet-stream";
    tmp[".talk"] = "text/x-speech";
    tmp[".tar"] = "application/x-tar";
    tmp[".taz"] = "application/x-tar";
    tmp[".tbp"] = "application/x-timbuktu";
    tmp[".tbt"] = "application/x-timbuktu";
    tmp[".tcl"] = "application/x-tcl";
    tmp[".tex"] = "application/x-tex";
    tmp[".texi"] = "application/x-texinfo";
    tmp[".texinfo"] = "application/x-texinfo";
    tmp[".tgz"] = "application/x-tar";
    tmp[".thm"] = "application/vnd.eri.thm";
    tmp[".tif"] = "image/tiff";
    tmp[".tiff"] = "image/tiff";
    tmp[".tki"] = "application/x-tkined";
    tmp[".tkined"] = "application/x-tkined";
    tmp[".toc"] = "application/toc";
    tmp[".toy"] = "image/toy";
    tmp[".tr"] = "application/x-troff";
    tmp[".trk"] = "x-lml/x-gps";
    tmp[".trm"] = "application/x-msterminal";
    tmp[".tsi"] = "audio/tsplayer";
    tmp[".tsp"] = "application/dsptype";
    tmp[".tsv"] = "text/tab-separated-values";
    tmp[".tsv"] = "text/tab-separated-values";
    tmp[".ttf"] = "application/octet-stream";
    tmp[".ttz"] = "application/t-time";
    tmp[".txt"] = "text/plain";
    tmp[".ult"] = "audio/x-mod";
    tmp[".ustar"] = "application/x-ustar";
    tmp[".uu"] = "application/x-uuencode";
    tmp[".uue"] = "application/x-uuencode";
    tmp[".vcd"] = "application/x-cdlink";
    tmp[".vcf"] = "text/x-vcard";
    tmp[".vdo"] = "video/vdo";
    tmp[".vib"] = "audio/vib";
    tmp[".viv"] = "video/vivo";
    tmp[".vivo"] = "video/vivo";
    tmp[".vmd"] = "application/vocaltec-media-desc";
    tmp[".vmf"] = "application/vocaltec-media-file";
    tmp[".vmi"] = "application/x-dreamcast-vms-info";
    tmp[".vms"] = "application/x-dreamcast-vms";
    tmp[".vox"] = "audio/voxware";
    tmp[".vqe"] = "audio/x-twinvq-plugin";
    tmp[".vqf"] = "audio/x-twinvq";
    tmp[".vql"] = "audio/x-twinvq";
    tmp[".vre"] = "x-world/x-vream";
    tmp[".vrml"] = "x-world/x-vrml";
    tmp[".vrt"] = "x-world/x-vrt";
    tmp[".vrw"] = "x-world/x-vream";
    tmp[".vts"] = "workbook/formulaone";
    tmp[".wav"] = "audio/x-wav";
    tmp[".wax"] = "audio/x-ms-wax";
    tmp[".wbmp"] = "image/vnd.wap.wbmp";
    tmp[".web"] = "application/vnd.xara";
    tmp[".wi"] = "image/wavelet";
    tmp[".wis"] = "application/x-InstallShield";
    tmp[".wm"] = "video/x-ms-wm";
    tmp[".wma"] = "audio/x-ms-wma";
    tmp[".wmd"] = "application/x-ms-wmd";
    tmp[".wmf"] = "application/x-msmetafile";
    tmp[".wml"] = "text/vnd.wap.wml";
    tmp[".wmlc"] = "application/vnd.wap.wmlc";
    tmp[".wmls"] = "text/vnd.wap.wmlscript";
    tmp[".wmlsc"] = "application/vnd.wap.wmlscriptc";
    tmp[".wmlscript"] = "text/vnd.wap.wmlscript";
    tmp[".wmv"] = "audio/x-ms-wmv";
    tmp[".wmx"] = "video/x-ms-wmx";
    tmp[".wmz"] = "application/x-ms-wmz";
    tmp[".wpng"] = "image/x-up-wpng";
    tmp[".wpt"] = "x-lml/x-gps";
    tmp[".wri"] = "application/x-mswrite";
    tmp[".wrl"] = "x-world/x-vrml";
    tmp[".wrz"] = "x-world/x-vrml";
    tmp[".ws"] = "text/vnd.wap.wmlscript";
    tmp[".wsc"] = "application/vnd.wap.wmlscriptc";
    tmp[".wv"] = "video/wavelet";
    tmp[".wvx"] = "video/x-ms-wvx";
    tmp[".wxl"] = "application/x-wxl";
    tmp[".x"] = "gzip application/x-gzip";
    tmp[".xar"] = "application/vnd.xara";
    tmp[".xbm"] = "image/x-xbitmap";
    tmp[".xdm"] = "application/x-xdma";
    tmp[".xdma"] = "application/x-xdma";
    tmp[".xdw"] = "application/vnd.fujixerox.docuworks";
    tmp[".xht"] = "application/xhtml+xml";
    tmp[".xhtm"] = "application/xhtml+xml";
    tmp[".xhtml"] = "application/xhtml+xml";
    tmp[".xla"] = "application/vnd.ms-excel";
    tmp[".xlc"] = "application/vnd.ms-excel";
    tmp[".xll"] = "application/x-excel";
    tmp[".xlm"] = "application/vnd.ms-excel";
    tmp[".xls"] = "application/vnd.ms-excel";
    tmp[".xlt"] = "application/vnd.ms-excel";
    tmp[".xlw"] = "application/vnd.ms-excel";
    tmp[".xm"] = "audio/x-mod";
    tmp[".xml"] = "text/xml";
    tmp[".xmz"] = "audio/x-mod";
    tmp[".xpi"] = "application/x-xpinstall";
    tmp[".xpm"] = "image/x-xpixmap";
    tmp[".xsit"] = "text/xml";
    tmp[".xsl"] = "text/xml";
    tmp[".xul"] = "text/xul";
    tmp[".xwd"] = "image/x-xwindowdump";
    tmp[".xyz"] = "chemical/x-pdb";
    tmp[".yz1"] = "application/x-yz1";
    tmp[".z"] = "application/x-compress";
    tmp[".zac"] = "application/x-zaurus-zac";
    tmp[".zip"] = "application/zip";
    return tmp;
}
