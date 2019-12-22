select ktosoll, sum(betrag) from journal where kostenstelle in (101) group by ktosoll order by ktosoll

select ktosoll, sum(betrag) 
from journal 
where kostenstelle in (401, 402, 403, 404, 405, 406, 407, 408, 409) 
group by ktosoll 
order by ktosoll


select ktohaben, sum(betrag) 
from journal 
where kostenstelle in (471) 
group by ktohaben 
order by ktohaben


select j.ktosoll, cu.idParentCostUnit, sum(j.betrag) from journal j, CostUnit cu
where j.KOSTENSTELLE = cu.idCostUnit
group by j.ktosoll, cu.idParentCostUnit
order by cu.idParentCostUnit, j.ktosoll


select j.ktosoll, a.textAccount, cu.idParentCostUnit, sum(j.betrag) 
from journal j, CostUnit cu, Account a
where j.KOSTENSTELLE = cu.idCostUnit
and j.ktosoll = a.idAccount
and j.ktosoll >= 2000 
and j.ktosoll < 9000
group by j.ktosoll, cu.idParentCostUnit
order by cu.idParentCostUnit, j.ktosoll

-- finale WRIV Auswertung

select 'Soll', j.ktosoll, a.textAccount, cu.idParentCostUnit, sum(j.betrag) 
from journal j, CostUnit cu, Account a
where j.KOSTENSTELLE = cu.idCostUnit
and j.ktosoll = a.idAccount
and j.ktosoll >= 2000 
and j.ktosoll < 9000
group by j.ktosoll, cu.idParentCostUnit
union
select 'Haben', j.ktohaben, a.textAccount, cu.idParentCostUnit, sum(j.betrag) 
from journal j, CostUnit cu, Account a
where j.KOSTENSTELLE = cu.idCostUnit
and j.ktohaben = a.idAccount
and j.ktohaben >= 2000 
and j.ktohaben < 9000
group by j.ktohaben, cu.idParentCostUnit
order by 1, cu.idParentCostUnit, j.ktohaben









"0"
"101"
"105"
"401"
"402"
"403"
"404"
"405"
"406"
"408"
"411"
"421"
"422"
"441"
"461"
"471"