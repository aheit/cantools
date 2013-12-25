#include "mdfmodel.h"

id_block_t *
id_block_get(const mdf_t *const mdf)
{
  return (id_block_t *)mdf->base;
}

hd_block_t *
hd_block_get(const mdf_t *const mdf)
{
  return (hd_block_t *)(mdf->base+64);
}

dg_block_t *
dg_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (dg_block_t *)(mdf->base+lnk);
}

cg_block_t *
cg_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (cg_block_t *)(mdf->base+lnk);
}

cn_block_t *
cn_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (cn_block_t *)(mdf->base+lnk);
}

ce_block_t *
ce_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (ce_block_t *)(mdf->base+lnk);
}

tx_block_t *
tx_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (tx_block_t *)(mdf->base + lnk);
}

const char *
tx_block_get_text(const mdf_t *const mdf, link_t lnk)
{
  if(lnk == 0) return NULL;
  return &((tx_block_t *)(mdf->base + lnk))->text1;
}

pr_block_t *
pr_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (pr_block_t *)(mdf->base + lnk);
}

dr_block_t *
dr_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (dr_block_t *)(mdf->base + lnk);
}

cc_block_t *
cc_block_get(const mdf_t *const mdf, const link_t lnk)
{
  if(lnk == 0) return NULL;
  return (cc_block_t *)(mdf->base + lnk);
}

const char *
cn_get_long_name(const mdf_t *const mdf, const cn_block_t *const cn_block)
{
  const char *name = tx_block_get_text(mdf, cn_block->link_asam_mcd_name);
  if(name==NULL) name = cn_block->signal_name;
  return name;
}
