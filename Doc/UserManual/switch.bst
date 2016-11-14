% Generic bibliography style file
% for use with the compact data base format of jw7.bib
% by Joachim Wuttke and collaborators.


% Make permanent edits  only in sc-intern/bib/switch.bib;
% then copy to application directory.

% Change switches only in the application directory.


% A litle history:
% - copied from BibTeX standard bibliography style `abbrv' 17nov93
%     version 0.99a for BibTeX versions 0.99a or later, LaTeX version 2.09.
% - changed to switch.bst 21nov97


INTEGERS { switch sw.lablenauto sw.namemaju sw.yearpos sw.name sw.journit
           sw.titlit sw.journco sw.volbf sw.wutex sw.lang sw.thebib
           sw.title sw.pf sw.names.and
           nameptr namesleft numnames nam_max_voll nam_min_etal }
STRINGS  { wrd.and wrd.edd sw.namesep sw.namesterm sw.titleterm }

%=============================================================================%

FUNCTION {choices} {
   #1 'switch :=       % main style switch
   #0 'sw.wutex :=     % my own definitions (from wubib.sty etc.)
   #1 'sw.lang :=      % language (1) engl (2) deutsch
   #1 'sw.thebib :=    % \references (0) or \begin{bibliography} (1)

   #99 'nam_max_voll := % max. number of authors
   #1 'nam_min_etal := % number of authors if etal is used
      %   nam_min_etal #1 + nam_max_voll <
      %      { "please set nam_min_etal < nam_max_voll " warning$ } {} if$
}

%=============================================================================%

FUNCTION {initialize.switches} {

    % default settings
    #1  'sw.name :=       % author name format: 1=Y. Su|2=Su Y.|3=Su Yi|4=Su, Y.
    #0  'sw.namemaju :=   % author name as small caps?
    "," 'sw.namesep :=    % author names separator
    #1  'sw.names.and :=  % last author separated by wrd.and
    "," 'sw.namesterm :=  % terminates author list
    #0  'sw.title :=      % print title?
    #0  'sw.titlit :=     % titles italicized?
    ". " 'sw.titleterm :=  % terminates title
    #0  'sw.yearpos :=    % year at position: 0=v,p(y)|1=v(y)p|3=Y,v,p
    #1  'sw.journit :=    % journal in italics?
    #0  'sw.journco :=    % comma after journal
    #1  'sw.volbf :=      % volume boldface?
    #0  'sw.pf :=         % print final page?

    % language-dependent defaults
    #1 sw.lang = {
       "and" 'wrd.and :=
       "edited by" 'wrd.edd :=
    } {} if$
    #2 sw.lang = {
       "und" 'wrd.and :=
       "hrsg. von" 'wrd.edd :=
    } {} if$

    % PhysRev
    #1 switch = {
       #1 'sw.lablenauto :=
       #0 'sw.journit :=
    } {} if$
    % PhysRevLett
    #2 switch = {
       #1 'sw.lablenauto :=
       #0 'sw.journit :=
       #4 'nam_max_voll :=
    } {} if$
    % J Phys
    #4 switch = {
       #0 'sw.lablenauto :=
       #2 'sw.yearpos :=
       #3 'sw.name :=
       #1 'sw.title :=
    } {} if$
    % Chikago
    #5 switch = {
       #1 'sw.lablenauto :=
       #3 'sw.yearpos :=
       #4 'sw.name :=
       #0 'sw.volbf :=
       #1 'sw.title :=
       #1 'sw.pf :=
       ";" 'sw.namesep :=
       "\ " 'sw.namesterm :=
       #0  'sw.names.and :=
    } {} if$
    % SIAM
    #6 switch = {
       #1 'sw.lablenauto :=
       #1 'sw.yearpos :=
       #1 'sw.name :=
       #1  'sw.namemaju :=   % author name as small caps
       #0 'sw.volbf :=
       #0  'sw.journit :=    % journal not in italics
       #1 'sw.title :=
       #1  'sw.titlit :=     % titles italicized
       ", " 'sw.titleterm :=  % terminates title
       #1 'sw.pf :=
       "," 'sw.namesep :=
       ", " 'sw.namesterm :=
       #1  'sw.names.and :=
       "{\sc and}" 'wrd.and :=
    } {} if$

}

ENTRY
  { % address
    a % author
    b % booktitle, for @inbook
    bv% bookvolume (mehrb"andiges Werk)
    c % copy (C/R/P/..)
    chapter
    cm % number in cond-mat
    dmy % full date (day-month-year, for newspapers)
    doi
    e % editor
    en% edition
    f % publisher (ferlach)
    g % type (genre)
    howpublished
    i % institution
    j % journal
    key
    l % location of publisher (NEW)
    mark
    month
    note
    n % number
    o % organization
    p % page
    pf % end page
    ri% remark - initial
    rf% remark - final
    s % series
    t % title
    u % school (universit"at)
    v % volume
    x % annote
    y % year
    yf% year of first edition (NEW)
  }
  {}
  { label }

MACRO {jan} {"Jan."}
MACRO {feb} {"Feb."}
MACRO {mar} {"Mar."}
MACRO {apr} {"Apr."}
MACRO {may} {"May"}
MACRO {jun} {"June"}
MACRO {jul} {"July"}
MACRO {aug} {"Aug."}
MACRO {sep} {"Sept."}
MACRO {oct} {"Oct."}
MACRO {nov} {"Nov."}
MACRO {dec} {"Dec."}

MACRO {subm} {"submitted"}
MACRO {inpr} {"in press"}
MACRO {unpu} {"unpublished"}
MACRO {tobe} {"to be published"}
MACRO {thissue} {"in this issue"}

% transitioning -> ordering by label (and not by official abbreviation)

MACRO{aasNY}{"Ann.\ NY Acad.\ Sci."}
MACRO{acie} {"Angew.\ Chem.\ Int.\ Ed."}
MACRO{acsmi}{"ACS Appl.\ Mater.\ Interfaces"}
MACRO{acp}  {"Adv.\ Chem.\ Phys."}
MACRO{acsss}{"Am.~Chem.\ Soc.\ Symp.\ Ser."}
MACRO{aipcp}{"AIP Conf.\ Proc."}
MACRO{ajp}  {"Am.~J.\ Phys."}
MACRO{amm}  {"Acta metall.\ mater."}
MACRO{ammm} {"Am.\ Math.\ Mon."}
MACRO{amse} {"Adv.\ Mat.\ Sci.\ Eng."}
MACRO{apl}  {"Appl.\ Phys.\ Lett."}
MACRO{apA}  {"Appl.\ Phys.\ A"}
MACRO{apLg} {"Ann.\ Phys.\ (Leipzig)"}
MACRO{apNY} {"Ann.\ Phys.\ (New York)"} %
MACRO{apPa} {"Ann.\ Phys.\ (Paris)"} %
MACRO{arpc} {"Ann.\ Rev.\ Phys.\ Chem."} %
MACRO{aop}  {"Appl. Optics"}
MACRO{asp}  {"Appl.\ Spectrosc."}
MACRO{assp} {"Adv.\ Solid State Phys.\ (Festk\ouml rperprobleme)"}
% define outside the bibtex environment: \def\ouml{\"o}
MACRO{avp}  {"Adv.\ Phys."}
MACRO{avpc} {"Adv.\ Phys.\ Chem."}
MACRO{ax}   {"Acta Cryst."}
MACRO{axA}  {"Acta Cryst.\ A"}
MACRO{axB}  {"Acta Cryst.\ B"}
MACRO{axC}  {"Acta Cryst.\ C"}
MACRO{axD}  {"Acta Cryst.\ D"}
MACRO{bbu}  {"Ber.\ Bunsenges.\ Phys.\ Chem."}
MACRO{bc}   {"Biochem."}
MACRO{bba}  {"Biochim.\ Biophys.\ Acta"}
MACRO{bcj}  {"Biochem.~J."}
MACRO{bcsj} {"Bull.\ Chem.\ Soc.\ Japan"}
MACRO{bpc}  {"Biophys.\ Chem."}
MACRO{bpj}  {"Biophys.~J."}
MACRO{bpm}  {"Biopolym."}
MACRO{cc}   {"Chem.\ Comm."}
MACRO{cp}   {"Chem.\ Phys."}
MACRO{cpchem}{"ChemPhysChem"}
MACRO{cpc}  {"Comput.~Phys.~Comm."}
MACRO{cpl}  {"Chem.\ Phys.\ Lett."}
MACRO{crv}  {"Chem.\ Rev."}
MACRO{cps}  {"Colloid Polymer Sci."}
MACRO{csr}  {"Chem.\ Soc.\ Rev."}
MACRO{cssp} {"Comm.\ Sol.\ State Phys."}
MACRO{cop}  {"Contemporary Phys."}
MACRO{crasB}{"C.~R.\ Acad.\ Sc.\ Paris B"}
MACRO{dan}  {"Dok.\ Akad.\ Nauk SSSR"}
MACRO{ddf}  {"Defect Diffus.\ Forum"}
MACRO{dm}   {"Discrete Math."}
MACRO{ebpj} {"Eur.\ Biophys.~J."}
MACRO{ecb}  {"Eur.\ Chem.\ Bull."}
MACRO{epjB} {"Eur.\ Phys.~J.\ B"}
MACRO{epjE} {"Eur.\ Phys.~J.\ E"}
MACRO{epjST} {"Eur.\ Phys.~J.\ Special Topics"}
MACRO{epl}  {"Europhys.\ Lett."}
MACRO{epl0} {"EPL"}
MACRO{Fd}   {"Faraday Discuss."}
MACRO{febsl}{"Fed.\ Eur. Biochem.\ Soc.\ Lett."}
MACRO{fscs} {"Faraday Symp.\ Chem.\ Soc."}
MACRO{hfi}  {"Hyperfine Interactions"}
MACRO{ijbmm}{"Int.~J.\ Biol.\ Macromol."}
MACRO{ijps} {"Int.~J.\ Phys.\ Sci."}
MACRO{ijtp} {"Int.~J.\ Thermophys."}
MACRO{itse} {"IEEE T.\ Software Eng."}
MACRO{jACmp}{"J.~Alloys Comp."}
MACRO{jacs} {"J.~Am.\ Chem.\ Soc."}
MACRO{jaces}{"J.~Am.\ Ceram.\ Soc."}
MACRO{jasa} {"J.~Acoust.\ Soc.\ Am."}
MACRO{jap}  {"J.~Appl.\ Phys."}
MACRO{jax}  {"J.~Appl.\ Cryst."}
MACRO{jbp}  {"J.~Biol.\ Phys."}
MACRO{jcam} {"J.~Comp.\ Appl.\ Math."}
MACRO{jced} {"J.~Chem.\ Eng.\ Data"}
MACRO{jcis} {"J.~Coll.\ Interf.\ Sci."}
MACRO{jcp}  {"J.~Chem.\ Phys."}
MACRO{jcpF} {"J.~Chim.\ Phys."}
MACRO{jcsf1}{"J.~Chem.\ Soc., Faraday Trans. 1"}
MACRO{jcsf2}{"J.~Chem.\ Soc., Faraday Trans. 2"}
MACRO{jcompp} {"J.~Comput.\ Phys."}
MACRO{jetpl}{"JETP Lett."}
MACRO{jjap} {"Japan.\ J.~Appl.\ Phys."}
MACRO{jlpt} {"J.~Low.\ Temp.\ Phys."}
MACRO{jmb}  {"J.~Mol.\ Biol."}
MACRO{jmgr} {"J.~Magn.\ Res."}
MACRO{jml}  {"J.~Mol.\ Liq."}
MACRO{jmmm} {"J.~Magn.\ Magn.\ Mater."}
MACRO{jmp}  {"J.~Math.\ Phys."}
MACRO{jmr}  {"J.~Mat.\ Res."}
MACRO{jms}  {"J.~Mol.\ Struct."}
MACRO{jncs} {"J.~Non-Cryst.\ Solids"}
MACRO{jnr}  {"J.~Neutron Res."}
MACRO{jpc}  {"J.~Phys.\ Chem."}
MACRO{jpcA} {"J.~Phys.\ Chem. A"}
MACRO{jpcB} {"J.~Phys.\ Chem. B"}
MACRO{jpcbp}{"J.~Phys.\ Chem. Biophys."}
MACRO{jpcC} {"J.~Phys.\ Chem. C"}
MACRO{jpcl} {"J.~Phys.\ Chem.\ Lett."}
MACRO{jpcs} {"J.~Phys.\ Chem.\ Solids"}
MACRO{jp}   {"J.~Phys."}
MACRO{jpi}  {"J.~Phys.\ A"}
MACRO{jpii} {"J.~Phys.\ B"}
MACRO{jpiii}{"J.~Phys.\ C"}
MACRO{jpiv} {"J.~Phys.~D: Appl.\ Phys."}
MACRO{jpCM} {"J.~Phys.\ Condens. Matter"}
MACRO{jpCf} {"J.~Phys.: Conf.\ Ser."}
MACRO{jpEsi}{"J.~Phys.\ E Sci.\ Instr."}
MACRO{jpMP} {"J.~Phys.\ F Metal Phys."}
MACRO{jpF} {"J.~Phys.\ France"}
MACRO{jpFi} {"J.~Phys.\ I (France)"}
MACRO{jpP}  {"J.~Phys.\ (Paris)"}
MACRO{jpPL} {"J.~Physique Lett."}
MACRO{jprad}{"J.~Phys.\ Radium"}
MACRO{jpsJ} {"J.~Phys.\ Soc.\ Jpn."}
MACRO{jPmSB}{"J.~Polym.\ Sci.\ B"}
MACRO{jrsi} {"J.~Roy.\ Soc.\ Interf."}
MACRO{jrNBS}{"J.~Res.\ N.~B.~S."}
MACRO{jsp}  {"J.~Stat.\ Phys."}
MACRO{jsyr} {"J.~Synchrotron Rad."}
MACRO{lnm}  {"Lect. Notes Math."} % currectly unusable cause number must be in s
MACRO{mam}  {"Macromolecules"}
MACRO{mclc} {"Mol.\ Cryst.\ Liq.\ Cryst."}
MACRO{mop}  {"Mol.\ Phys."}
MACRO{mos}  {"Molec.\ Sim."}
MACRO{mplB} {"Mod.\ Phys.\ Lett.\ B"}
MACRO{mrssp}{"Mat.\ Res.\ Soc.\ Symp.\ Proc."}
MACRO{mst}  {"Meas.\ Sci.\ Technol."}
MACRO{nat}  {"Nature"}
MACRO{natCo}{"Nature Commun."}
MACRO{natPh}{"Nature Photonics"}
MACRO{naw}  {"Naturwiss."}
MACRO{ncD}  {"Nuovo Cimento D"}
MACRO{nim}  {"Nucl.\ Inst.\ Meth."}
MACRO{nimA} {"Nucl.\ Inst.\ Meth.\ A"}
MACRO{nimB} {"Nucl.\ Inst.\ Meth.\ B"}
MACRO{njp}  {"New J.~Phys."}
MACRO{nl}   {"Nanoletters"}
MACRO{nn}   {"Neutron News"}
MACRO{nnt}  {"Nano\-techno\-logy"}
MACRO{nse}  {"Nucl.\ Sci.\ Eng."}
MACRO{phm}  {"Philos.\ Mag."}
MACRO{phmB} {"Philos.\ Mag.\ B"}
MACRO{pht}  {"Phase Transit."}
MACRO{ptrs} {"Phil.\ Trans.\ Roy.\ Soc.\ Lond."}
MACRO{ptrsB}{"Phil.\ Trans.\ Roy.\ Soc.\ Lond.\ B"}
MACRO{pbl}  {"Phys.\ Bl."}
MACRO{pccp} {"Phys.\ Chem.\ Chem.\ Phys."}
MACRO{pcs}  {"Phys.\ Chem.\ Solids"}
MACRO{pl}   {"Phys.\ Lett."}
MACRO{plA}  {"Phys.\ Lett.\ A"}
MACRO{plC}  {"Phys.\ Lett.\ C"}
MACRO{plCR} {"Phys.\ Rep."}
MACRO{pnas} {"Proc.\ Natl.\ Acad.\ Sci.\ USA"}
MACRO{pnasus}{"Proc.\ Natl.\ Acad.\ Sci.\ USA"} % obsolete
MACRO{pogg} {"Pogg.\ Ann.\ Phys."}
MACRO{poly} {"Polymer"}
MACRO{pr}   {"Phys.\ Rev."}
MACRO{prA}  {"Phys.\ Rev.\ A"}
MACRO{prB}  {"Phys.\ Rev.\ B"}
MACRO{prE}  {"Phys.\ Rev.\ E"}
MACRO{prep} {"Phys.\ Reports"}
MACRO{prl}  {"Phys.\ Rev.\ Lett."}
MACRO{prsA} {"Proc.\ Roy.\ Soc.\ A"}
MACRO{pps}  {"Proc.\ Phys.\ Soc."}
MACRO{ppsB} {"Proc.\ Phys.\ Soc.\ B"}
MACRO{pcps} {"Progr.\ Coll.\ Polym.\ Sci."}
MACRO{psc}  {"Phys.\ Script."}
MACRO{pscT} {"Phys.\ Script.\ T"}
MACRO{pss}  {"Progr.\ Surf.\ Sci."}
MACRO{pt}   {"Phys.\ Today"}
MACRO{ptp}  {"Prog.\ Theor.\ Phys."}
MACRO{ptps} {"Prog.\ Theor.\ Phys.\ Suppl."}
MACRO{py}   {"Physica"}
MACRO{pyA}  {"Physica\ A"}
MACRO{pyB}  {"Physica\ B"}
MACRO{pyBC} {"Physica\ B$+$C"}
MACRO{pyZ}  {"Physik.~Z."}
MACRO{pzSU} {"Physik.~Z.\ Sowjet."}
MACRO{rpp}  {"Rep.\ Progr.\ Phys."}
MACRO{qrbp} {"Q.~Rev.\ Biophys."}
MACRO{rmp}  {"Rev.\ Mod.\ Phys."}
MACRO{rsi}  {"Rev.\ Sci.\ Instr."}
MACRO{sca}  {"Sci.\ Am."}
MACRO{sc}   {"Science"}
MACRO{siamjam}{"SIAM J.~Appl.\ Math."}
MACRO{siamjna}{"SIAM J.~Numer.\ Anal."}
MACRO{spp}  {"Springer Proceedings in Physics"}
MACRO{ssc}  {"Solid State Commun."}
MACRO{ssmr} {"Solid State Magn.\ Reson."}
MACRO{sjetp}{"Sov.\ Phys.\ --- JETP"}
MACRO{spss} {"Sov.\ Phys.\ --- Solid State"}
MACRO{tfs}  {"Trans.\ Faraday Soc."}
MACRO{toms} {"ACM T. Math. Software"}
MACRO{ttsp} {"Transp.\ Theory Stat.\ Phys."}
MACRO{vdpgVI}{"Verhandl.\ DPG (VI)"}
MACRO{zn}   {"Z.~Naturforsch."}
MACRO{zp}   {"Z.~Phys."}
MACRO{zpB}  {"Z.~Phys.\ B"}
MACRO{zpcnf}{"Z.~Phys.\ Chem.\ N.~F."}
MACRO{PLcb} {"PLoS Comput.\ Biol."}
MACRO{PLONE}{"PLoS ONE"}
MACRO{Rjetp}{"JETP"} % {"Zh. Exp. Teor. Fyz."}   % R : in Russian

INTEGERS { output.state before.all mid.sentence after.sentence after.block }

FUNCTION {init.state.consts}
{ #0 'before.all :=
  #1 'mid.sentence :=
  #2 'after.sentence :=
  #3 'after.block :=
}

STRINGS { stri stro }

FUNCTION {output.nonnull}
{ 'stri :=
  output.state mid.sentence =
    { write$ }        % WAR { ", " * write$ }
    { output.state after.block =
	{ write$      % WAR add.period$ write$
%	  newline$
%	  "\G " write$ % \G is shorthand for \newblock
	}
	{ output.state before.all =
	    'write$
        % else output.state after.block =
	    'write$ % WAR { add.period$ " " * write$ }
	  if$
	}
      if$
      mid.sentence 'output.state :=
    }
  if$
  stri
}

FUNCTION {output}
{ duplicate$ empty$
    'pop$
    'output.nonnull
  if$
}

FUNCTION {output.check}
{ 'stro :=
  duplicate$ empty$
    { pop$ "empty " stro * " in " * cite$ * warning$ }
    'output.nonnull
  if$
}

FUNCTION {output.bibitem}
{ newline$
  sw.wutex { "\E" } { "\bibitem" } if$ write$
  mark empty$ {} { "[" write$ mark write$ "]" write$ } if$
  "{" write$
  cite$ write$ "}" write$
   "" %  MODIF
  before.all 'output.state :=
  ri empty$ {} { ri " " * output } if$
}

FUNCTION {output.note}
{ note empty$ {} {
    add.period$
    " " note * output
  } if$
}

FUNCTION {fin.entry}
{
  rf empty$ {} { ". " rf * output } if$
  add.period$ % CHANGE
  write$
  newline$
}

FUNCTION {new.block}
{ output.state before.all =
    'skip$
    { after.block 'output.state := }
  if$
}

FUNCTION {new.sentence}
{ output.state after.block =
    'skip$
    { output.state before.all =
	'skip$
	{ after.sentence 'output.state := }
      if$
    }
  if$
}

FUNCTION {not}
{   { #0 }
    { #1 }
  if$
}

FUNCTION {and}
{   'skip$
    { pop$ #0 }
  if$
}

FUNCTION {or}
{   { pop$ #1 }
    'skip$
  if$
}

FUNCTION {new.block.checka}
{ empty$
    'skip$
    'new.block
  if$
}

FUNCTION {new.block.checkb}
{ empty$
  swap$ empty$
  and
    'skip$
    'new.block
  if$
}

FUNCTION {new.sentence.checka}
{ empty$
    'skip$
    'new.sentence
  if$
}

FUNCTION {new.sentence.checkb}
{ empty$
  swap$ empty$
  and
    'skip$
    'new.sentence
  if$
}

FUNCTION {field.or.null}
{ duplicate$ empty$
    { pop$ "" }
    'skip$
  if$
}

FUNCTION {emphasize}
{ duplicate$ empty$
    { pop$ "" }
    { "{\em " swap$ * "}" * }
  if$
}

FUNCTION {format.names}
{ 'stri :=
  #1 'nameptr :=
  stri num.names$ 'numnames :=
  numnames nam_max_voll > { nam_min_etal #1 + } { numnames } if$ 'namesleft :=
  { namesleft #0 > }
  { stri nameptr
    sw.name #1 = { "{f.~}{vv~}{ll}{, jj}" format.name$ } {
    sw.name #2 = { "{vv~}{ll~}{f.}" format.name$ } {
    sw.name #3 = { "{vv~}{ll~}{ff}" format.name$ } {
    sw.name #4 = { "{vv~}{ll,~}{f.}" format.name$ } {
    "sw.name o.o.r." warning$ } if$ } if$ } if$ } if$
    sw.namemaju { "{\sc " swap$ * "}" * } {} if$
    'stro :=

    nameptr #1 >
    { namesleft #1 >
      { sw.namesep * " " * stro * } % between #(i) and #(i+1) for i=1,n-2
      { stro "others " = stro "others" = or nameptr numnames < or
	{ " {\em et~al.}" * }
	{ sw.names.and { " " * wrd.and } { sw.namesep } if$
          * " " * stro * } % CHANGE " and " / ", "
        if$
      }
      if$
    }
    'stro
    if$
    nameptr #1 + 'nameptr :=
    namesleft #1 - 'namesleft :=
  }
  while$
}

FUNCTION {format.authors}
{ a empty$
    { "" }
    { a format.names *
      sw.yearpos #2 =
        { y empty$ { "\ " } { " (" y * ") " *} if$ }
        { sw.namesterm " " *}
      if$
    } if$
}

FUNCTION {format.editors}
{ e empty$
    { "" }
    { ", " wrd.edd * " " * e format.names * }
  if$
}

FUNCTION {format.title}
{ t empty$
    { "" }
    { sw.titlit #0 = { t } { "\textit{" t * "}" * } if$ }
  if$
}

FUNCTION {n.dashify}
{ 'stro :=
  ""
    { stro empty$ not }
    { stro #1 #1 substring$ "-" =
	{ stro #1 #2 substring$ "--" = not
	    { "--" *
	      stro #2 global.max$ substring$ 'stro :=
	    }
	    {   { stro #1 #1 substring$ "-" = }
		{ "-" *
		  stro #2 global.max$ substring$ 'stro :=
		}
	      while$
	    }
	  if$
	}
	{ stro #1 #1 substring$ *
	  stro #2 global.max$ substring$ 'stro :=
	}
      if$
    }
  while$
}

FUNCTION {format.date} {
   y empty$ {
      ""
   } {
      " ("  * y * ")"
   } if$
}

FUNCTION {format.bookdate} {
   y empty$ {
      ""
   } {
      " (" yf empty$ { } { * yf * ", " } if$
      en empty$ { } { * "$^{" * en * "}$" } if$
      * y * ")"
   } if$
}

FUNCTION {format.btitle}
{ t emphasize
}

FUNCTION {tie.or.space.connect}
{ duplicate$ text.length$ #3 <
    { "~" }
    { " " }
  if$
  swap$ * *
}

FUNCTION {either.or.check}
{ empty$
    'pop$
    { "can't use both " swap$ * " fields in " * cite$ * warning$ }
  if$
}

FUNCTION {format.bvolume}
{ bv empty$
    { "" }
    { "volume" bv tie.or.space.connect
      s empty$
	'skip$
	{ " of " * s emphasize * }
      if$
      "volume and number" n either.or.check
    }
  if$
}

FUNCTION {format.number.series} % for book/collection/proceedings in a series
{ s empty$
   { "" }
   { "\ (" s * % " " reicht nicht als blank hinter }\G
    v empty$
       { ")" * }
       { " " * v * ")" * }
       if$
    }
  if$
}

FUNCTION {format.edition}
{ en empty$
    { "" }
    { output.state mid.sentence =
	{ en "l" change.case$ " edition" * }
	{ en "t" change.case$ " edition" * }
      if$
    }
  if$
}

INTEGERS { multiresult }

FUNCTION {multi.page.check}
{ 'stro :=
  #0 'multiresult :=
    { multiresult not
      stro empty$ not
      and
    }
    { stro #1 #1 substring$
      duplicate$ "-" =
      swap$ duplicate$ "," =
      swap$ "+" =
      or or
	{ #1 'multiresult := }
	{ stro #2 global.max$ substring$ 'stro := }
      if$
    }
  while$
  multiresult
}

FUNCTION {format.pages}
{ p empty$
    { "" }
    sw.pf #0 = {
      p multi.page.check
  	{ "pages" p n.dashify tie.or.space.connect }
  	{ "page" p tie.or.space.connect }
      if$
    } {
      p
      pf empty$ {} { "--" * pf * } if$ *
    } if$
  if$
}

FUNCTION {format.vol.pages.date}
{ sw.yearpos #3 = {
    "{\bf " y * "}, " *
    v empty$ {} { v * ", " * } if$
    p empty$ {} { p n.dashify * pf empty$ sw.pf #0 = or {} { "--" * pf * } if$ } if$
  }
  {
    v empty$
      { "" }
      { sw.volbf { "{\bf " v * "}" * } { v } if$ }
    if$
    sw.yearpos #0 = {
      p empty$
        'skip$
        { duplicate$ empty$
	   { pop$ format.pages }
	   { ", " * p n.dashify * pf empty$ sw.pf #0 = or {} { "--" * pf * } if$ } % MOD
	 if$
      }
      if$
      format.date *
    } {
      sw.yearpos #1 = { format.date * } {} if$
      p empty$ {} { " " * p n.dashify * pf empty$ sw.pf #0 = or {} { "--" * pf * } if$ } if$
    } if$
  } if$
}

FUNCTION {format.no.date}
{ n empty$
    { "" }
    { "Nr.~" n * }
  if$
%  p empty$
%    'skip$
%    { duplicate$ empty$
%       { pop$ format.pages }
%       { ", " * p n.dashify * } if$
%  } if$
  dmy empty$
     'skip$ { ", " * dmy * } if$
}

FUNCTION {format.chapter.pages}
{ chapter empty$
    'format.pages
    { g empty$
	{ "chapter" }
	{ g "l" change.case$ }
      if$
      chapter tie.or.space.connect
      p empty$
	'skip$
	{ ", " * format.pages * }
      if$
    }
  if$
}

FUNCTION {format.in.ed.booktitle}
{ b empty$
    { "" }
    { e empty$
	{ "in " b emphasize * }
	{ "in " b emphasize * format.editors *}
      if$
    }
  if$
}

FUNCTION {empty.misc.check}
{ a empty$ t empty$ howpublished empty$
  month empty$ y empty$ note empty$
  and and and and and
  key empty$ not and
    { "all relevant fields are empty in " cite$ * warning$ }
    'skip$
  if$
}

FUNCTION {format.thesis.type}
{ g empty$
    'skip$
    { pop$
      g "t" change.case$
    }
  if$
}

FUNCTION {format.tr.number}
{ g empty$
    { "Technical Report" }
    'g
  if$
  n empty$
    { "t" change.case$ }
    { n tie.or.space.connect }
  if$
}

FUNCTION {format.er.number}
{ g empty$
    { "Experimental Report" }
    'g
  if$
  n empty$
    { "t" change.case$ }
    { n tie.or.space.connect }
  if$
}

FUNCTION {format.article.crossref}
{ key empty$
    { j empty$
	{ "need key or journal for " cite$ * " to crossref " * crossref *
	  warning$
	  ""
	}
	{ "In {\em " j * "\/}" * }
      if$
    }
    { "In " key * }
  if$
  " \cite{" * crossref * "}" *
}

FUNCTION {format.crossref.editor}
{ e #1 "{vv~}{ll}" format.name$
  e num.names$ duplicate$
  #2 >
    { pop$ " et~al." * }
    { #2 <
	'skip$
	{ e #2 "{ff }{vv }{ll}{ jj}" format.name$ "others" =
	    { " et~al." * }
	    { " " * wrd.and * " " * e #2 "{vv~}{ll}" format.name$ * }
	  if$
	}
      if$
    }
  if$
}

FUNCTION {format.book.crossref}
{ v empty$ % mu"s das hier v oder bv hei"sen ??
    { "empty volume in " cite$ * "'stri crossref of " * crossref * warning$
      "In "
    }
    { "Volume" v tie.or.space.connect
      " of " *
    }
  if$
  e empty$
  e field.or.null a field.or.null =
  or
    { key empty$
	{ s empty$
	    { "need editor, key, or series for " cite$ * " to crossref " *
	      crossref * warning$
	      "" *
	    }
	    { "{\em " * s * "\/}" * }
	  if$
	}
	{ key * }
      if$
    }
    { format.crossref.editor * }
  if$
  " \cite{" * crossref * "}" *
}

FUNCTION {format.incoll.inproc.crossref}
{ e empty$
  e field.or.null a field.or.null =
  or
    { key empty$
	{ b empty$
	    { "need editor, key, or booktitle for " cite$ * " to crossref " *
	      crossref * warning$
	      ""
	    }
	    { "In {\em " b * "\/}" * }
	  if$
	}
	{ "In " key * }
      if$
    }
    { "In " format.crossref.editor * }
  if$
  " \cite{" * crossref * "}" *
}

FUNCTION {preprintadd.if}
{ cm empty$ {}
    { ", cond-mat/" cm * output }
  if$
}

FUNCTION {preprintonly.if}
{ cm empty$ {}
    { "preprint cond-mat/" cm * output }
  if$
}

FUNCTION {Art} % Article
{ output.bibitem
  format.authors "author" output.check
  sw.title #1 = {
    new.block
    format.title "title" output.check sw.titleterm *
  } {} if$
  new.block
  crossref missing$ % seems to be always missing (???)
    { j missing$ {} {
        j sw.journit { "{\em " swap$ * "}" * } {} if$
        sw.journco { ", " } { " " } if$ *
        "journal" output.check % WAR journal emphasize
        format.vol.pages.date output
      } if$
    }
    { format.article.crossref output.nonnull
      format.pages output
    }
  if$
  preprintadd.if
  new.block
  note output
  fin.entry
}

FUNCTION {Nwp} % Newspaper
{ output.bibitem
  format.authors "author" output.check
  new.block
  j missing$ {} {
     j sw.journit { "{\em " swap$ * "}" * } {} if$
     sw.journco { ", " } { " " } if$ *
     "journal" output.check % WAR journal emphasize
     format.no.date output
  } if$
  new.block
  note output
  fin.entry
}

FUNCTION {Buk} % Book
{ output.bibitem
  a empty$
    { }
    { format.authors output.nonnull
      crossref missing$
	{ "author and editor" e either.or.check }
	'skip$
      if$
    }
  if$
  new.block
  format.btitle "btitle" output.check
  crossref missing$
    { format.bvolume output
      new.block
      format.number.series output
      a empty$
         { format.editors "author and editor" output.check }
         { }
         if$
      new.sentence
      f missing$ l missing$ and {} { ", " output } if$
      f "publisher" output.check % ferlach
      l missing$
      {} { ": " * l output} if$ % locus iste
%      address output
    }
    { new.block
      format.book.crossref output.nonnull
    }
  if$
%  format.edition output
  format.bookdate "year" output.check
  new.block
  output.note
  fin.entry
}

FUNCTION {booklet}
{ output.bibitem
  format.authors output
  new.block
  format.title "title" output.check
  howpublished l new.block.checkb
  howpublished output
  l output
  format.bookdate output
  new.block
  note output
  fin.entry
}

FUNCTION {iBk} % in Book
{ output.bibitem
  a empty$
    { format.editors "author and editor" output.check }
    { format.authors output.nonnull
      crossref missing$
	{ "author and editor" e either.or.check }
	'skip$
      if$
    }
  if$
  new.block
  format.btitle "title" output.check
  crossref missing$
    { format.bvolume output
      format.chapter.pages "chapter and pages" output.check
      new.block
      format.number.series output
      new.sentence
      f "publisher" output.check
      l output
    }
    { format.chapter.pages "chapter and pages" output.check
      new.block
      format.book.crossref output.nonnull
    }
  if$
%  format.edition output
  format.bookdate "year" output.check
  new.block
  note output
  fin.entry
}

FUNCTION {iCo} % {incollection}
{ output.bibitem
  format.authors "author" output.check
%  new.block
%  format.title "title" output.check
  new.block
  crossref missing$
    { format.in.ed.booktitle "booktitle" output.check
      format.bvolume output
      format.number.series output
%      format.chapter.pages output % ausgeschaltet wg kein Komma in LoBo94
      new.sentence
      f missing$ {} { ", " * f output } if$
      l missing$
      {} { ": " * l output} if$ % locus iste
%      format.edition output
      format.bookdate "year" output.check
    }
    { format.incoll.inproc.crossref output.nonnull
      format.chapter.pages output
    }
  if$
  new.block
  note output
  fin.entry
}

FUNCTION {iPr} % in Proceedings
{ output.bibitem
  format.authors "author" output.check
  new.block
  format.title "title" output.check
  new.block
  crossref missing$
    { format.in.ed.booktitle "booktitle" output.check
      format.bvolume output
      format.number.series output
      format.pages output
      l empty$
	{ o f new.sentence.checkb
	  o output
	  f output
	  format.date "year" output.check
	}
	{ l output.nonnull
	  format.date "year" output.check
	  new.sentence
	  o output
	  f output
	}
      if$
    }
    { format.incoll.inproc.crossref output.nonnull
      format.pages output
    }
  if$
  new.block
  note output
  fin.entry
}

FUNCTION {PiJ} % Proceedings in Journal / neu ab 17sep99
{ output.bibitem
  format.btitle "btitle" output.check
  new.block
  format.editors "editors" output.check
  new.block
  ", " *
  j sw.journit { "{\em " swap$ * "}" * } {} if$
  sw.journco { ", " } { " " } if$ *
  "journal" output.check % WAR journal emphasize
  format.vol.pages.date output
  new.block
  note output
  fin.entry
}

FUNCTION {conference} { iPr }

FUNCTION {manual}
{ output.bibitem
  a empty$
    { o empty$
	'skip$
	{ o output.nonnull
	  l output
	}
      if$
    }
    { format.authors output.nonnull }
  if$
  new.block
  format.btitle "title" output.check
  a empty$
    { o empty$
	{ l new.block.checka
	  l output
	}
	'skip$
      if$
    }
    { o l new.block.checkb
      o output
      l output
    }
  if$
%  format.edition output
  format.bookdate output
  new.block
  note output
  fin.entry
}

FUNCTION {mastersthesis}
{ output.bibitem
  format.authors "author" output.check
  new.block
  format.title "title" output.check
  new.block
  "Master's thesis" format.thesis.type output.nonnull
  u "school" output.check
  l output
  format.date "year" output.check
  new.block
  note output
  fin.entry
}

FUNCTION {Any} % misc
{ output.bibitem
  format.authors output
  t howpublished new.block.checkb
  format.title output
  howpublished new.block.checka
  howpublished output
  format.date output
  new.block
  note output
  fin.entry
  empty.misc.check
}

FUNCTION {Rem} % remark (text only, enter as title)
{ output.bibitem
  t output
  fin.entry
}

FUNCTION {phdthesis}
{ output.bibitem
  format.authors "author" output.check
  new.block
  format.btitle "title" output.check
  new.block
  "PhD thesis" format.thesis.type output.nonnull
  u "school" output.check
  l output
  format.date "year" output.check
  new.block
  note output
  fin.entry
}

FUNCTION {proceedings}
{ output.bibitem
  e empty$
    { o output }
    { format.editors output.nonnull }
  if$
  new.block
  format.btitle "title" output.check
  format.bvolume output
  format.number.series output
  l empty$
    { e empty$
	{ f new.sentence.checka }
	{ o f new.sentence.checkb
	  o output
	}
      if$
      f output
      format.date "year" output.check
    }
    { l output.nonnull
      format.date "year" output.check
      new.sentence
      e empty$
	'skip$
	{ o output }
      if$
      f output
    }
  if$
  new.block
  note output
  fin.entry
}

FUNCTION {The} % any thesis
{ output.bibitem
  format.authors "author" output.check
  new.block
  format.btitle "title" output.check
  ", " output
  new.block
  g "genre" output.check
  ", " output
  u "school" output.check
  l output
  format.date "year" output.check
  new.block
  note output
  fin.entry
}

FUNCTION {TDr} % "Dissertation"
{ output.bibitem
  format.authors "author" output.check
  new.block
%  "Dissertation, " output
  "PhD thesis, " output
  u "school" output.check
  l output
  format.date "year" output.check
  new.block
  note output
  fin.entry
}

FUNCTION {TDp} % "Diplomarbeit"
{ output.bibitem
  format.authors "author" output.check
  new.block
%  "Diplomarbeit, " output
  "diploma thesis, " output
  u "school" output.check
  l output
  format.date "year" output.check
  new.block
  note output
  fin.entry
}

FUNCTION {TRp} % Technical Report
{ output.bibitem
  format.authors "author" output.check
  new.block
  format.title "title" output.check
  new.block
  format.tr.number output.nonnull
  ", " * i "institution" output.check
  l missing$
  {} { ": " * l output} if$ % locus iste
  format.date "year" output.check
  new.block
  note output
  fin.entry
}

FUNCTION {ERp} % Experimental Report
{ output.bibitem
  format.authors "author" output.check
  new.block
  format.title "title" output.check
  new.block
  format.er.number output.nonnull
  ", " * i "institution" output.check
  l missing$
  {} { ": " * l output} if$ % locus iste
  format.date "year" output.check
  new.block
  note output
  fin.entry
}

FUNCTION {PCo} % "Personal Communication"
{ output.bibitem
  format.authors "author" output.check
  new.block
  "\BIBpcom\ " output
  format.date output
  note output
  fin.entry
}

FUNCTION {Unp} % unpublished
{ output.bibitem
  format.authors "author" output.check
  new.block
%  format.title "title" output.check
%  new.block
  note "note" output.check
  format.date output
  fin.entry
}

FUNCTION {default.type} { Any }

READ % <----------------------------------------------------------------------

FUNCTION {sortify}
{ purify$
  "l" change.case$
}

INTEGERS { len }

FUNCTION {chop.word}
{ 'stri :=
  'len :=
  stri #1 len substring$ =
    { stri len #1 + global.max$ substring$ }
    'stri
  if$
}

FUNCTION {sort.format.names}
{ 'stri :=
  #1 'nameptr :=
  ""
  stri num.names$ 'numnames :=
  numnames 'namesleft :=
    { namesleft #0 > }
    { nameptr #1 >
	{ "   " * }
	'skip$
      if$
      stri nameptr "{vv{ } }{ll{ }}{  f{ }}{  jj{ }}" format.name$ 'stro :=
      nameptr numnames = stro "others" = and
	{ "et al" * }
	{ stro sortify * }
      if$
      nameptr #1 + 'nameptr :=
      namesleft #1 - 'namesleft :=
    }
  while$
}

FUNCTION {sort.format.title}
{ 'stro :=
  "A " #2
    "An " #3
      "The " #4 stro chop.word
    chop.word
  chop.word
  sortify
  #1 global.max$ substring$
}

FUNCTION {author.sort}
{ a empty$
    { key empty$
	{ "to sort, need a or key in " cite$ * warning$
	  ""
	}
	{ key sortify }
      if$
    }
    { a sort.format.names }
  if$
}

FUNCTION {author.editor.sort}
{ a empty$
    { e empty$
	{ key empty$
	    { "to sort, need a, editor, or key in " cite$ * warning$
	      ""
	    }
	    { key sortify }
	  if$
	}
	{ e sort.format.names }
      if$
    }
    { a sort.format.names }
  if$
}

FUNCTION {author.organization.sort}
{ a empty$
    { o empty$
	{ key empty$
	    { "to sort, need a, organization, or key in " cite$ * warning$
	      ""
	    }
	    { key sortify }
	  if$
	}
	{ "The " #4 o chop.word sortify }
      if$
    }
    { a sort.format.names }
  if$
}

FUNCTION {editor.organization.sort}
{ e empty$
    { o empty$
	{ key empty$
	    { "to sort, need editor, organization, or key in " cite$ * warning$
	      ""
	    }
	    { key sortify }
	  if$
	}
	{ "The " #4 o chop.word sortify }
      if$
    }
    { e sort.format.names }
  if$
}

FUNCTION {presort}
{ type$ "book" =
  type$ "inbook" =
  or
    'author.editor.sort
    { type$ "proceedings" =
	'editor.organization.sort
	{ type$ "manual" =
	    'author.organization.sort
	    'author.sort
	  if$
	}
      if$
    }
  if$
  "    "
  *
  y field.or.null sortify
  *
  "    "
  *
  t field.or.null
  sort.format.title
  *
  #1 entry.max$ substring$
  'sort.key$ :=
}

%% ++++ here the final behaviour of .bst is chosen : ++++ %%

EXECUTE { choices }
EXECUTE { initialize.switches }

% ITERATE {presort}

% SORT

STRINGS { longest.label }

INTEGERS { number.label longest.label.width }

FUNCTION {initialize.longest.label}
{ "" 'longest.label :=
  #1 'number.label :=
  #0 'longest.label.width :=
}

FUNCTION {longest.label.pass}
{ number.label int.to.str$ 'label :=
  number.label #1 + 'number.label :=
  label width$ longest.label.width >
    { label 'longest.label :=
      label width$ 'longest.label.width :=
    }
    'skip$
  if$
}

EXECUTE {initialize.longest.label}

ITERATE {longest.label.pass} % not needed if revtex or wubib provide \references

FUNCTION {begin.bib}
{ preamble$ empty$
    'skip$
    { preamble$ write$ newline$ }
  if$
  #0 sw.thebib =
    { "\references" }
    { "\begin{thebibliography}{"  longest.label  * "}" * }
  if$
  write$ newline$
}

EXECUTE {begin.bib}

EXECUTE {init.state.consts}

ITERATE {call.type$}

FUNCTION {end.bib}
{ newline$
  #0 sw.thebib =
    { "\endreferences" }
    { "\end{thebibliography}" }
  if$
  write$ newline$
}

EXECUTE {end.bib}
