class FlowSeq( list ):
    pass


def yamlDump(filename, data):
    """
    Saves an arbitrary hierarchical data set as YAML-formatted text file.
    """
    import yaml
    global yaml
    from collections import OrderedDict

    class ImprovedDumper(yaml.Dumper):
        pass

    def odict_representer(dumper, data):
        return dumper.represent_mapping(
            yaml.resolver.BaseResolver.DEFAULT_MAPPING_TAG,
            data.items())

    def flowseq_representer(dumper, data):
        return dumper.represent_sequence(
            yaml.resolver.BaseResolver.DEFAULT_SEQUENCE_TAG,
            data,
            flow_style=True )
    ImprovedDumper.add_representer(OrderedDict, odict_representer)
    ImprovedDumper.add_representer(FlowSeq, flowseq_representer)
    with open(filename+".yaml", "w") as f:
        f.write(yaml.dump(data, None, ImprovedDumper,
                          allow_unicode=True, encoding='utf-8',
                          default_flow_style=False, indent=4, width=70).decode('utf-8'))
