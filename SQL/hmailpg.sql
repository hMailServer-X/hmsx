--
-- PostgreSQL database dump
--

-- Dumped from database version 10.19
-- Dumped by pg_dump version 10.19

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- Name: plpgsql; Type: EXTENSION; Schema: -; Owner: 
--

CREATE EXTENSION IF NOT EXISTS plpgsql WITH SCHEMA pg_catalog;


--
-- Name: EXTENSION plpgsql; Type: COMMENT; Schema: -; Owner: 
--

COMMENT ON EXTENSION plpgsql IS 'PL/pgSQL procedural language';


--
-- Name: hm_drop_table(character varying); Type: FUNCTION; Schema: public; Owner: hmail
--

CREATE FUNCTION public.hm_drop_table(tablename character varying) RETURNS void
    LANGUAGE plpgsql
    AS $$
DECLARE
	table_exists int4;
BEGIN
	SELECT into table_exists count(*) from pg_class where relname = tablename::name;
	if table_exists > 0 then
		execute 'DROP TABLE ' || tablename;
	end if;
END;$$;


ALTER FUNCTION public.hm_drop_table(tablename character varying) OWNER TO hmail;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- Name: hm_accounts; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_accounts (
    accountid bigint NOT NULL,
    accountdomainid integer NOT NULL,
    accountadminlevel smallint NOT NULL,
    accountaddress character varying(255) NOT NULL,
    accountpassword character varying(255) NOT NULL,
    accountactive smallint NOT NULL,
    accountisad smallint NOT NULL,
    accountaddomain character varying(255) NOT NULL,
    accountadusername character varying(255) NOT NULL,
    accountmaxsize integer NOT NULL,
    accountvacationmessageon smallint NOT NULL,
    accountvacationmessage text NOT NULL,
    accountvacationsubject character varying(200) NOT NULL,
    accountpwencryption smallint NOT NULL,
    accountforwardenabled smallint NOT NULL,
    accountforwardaddress character varying(255) NOT NULL,
    accountforwardkeeporiginal smallint NOT NULL,
    accountenablesignature smallint NOT NULL,
    accountsignatureplaintext text NOT NULL,
    accountsignaturehtml text NOT NULL,
    accountlastlogontime timestamp without time zone NOT NULL,
    accountvacationexpires smallint NOT NULL,
    accountvacationexpiredate timestamp without time zone NOT NULL,
    accountpersonfirstname character varying(60) NOT NULL,
    accountpersonlastname character varying(60) NOT NULL
);


ALTER TABLE public.hm_accounts OWNER TO hmail;

--
-- Name: hm_accounts_accountid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_accounts_accountid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_accounts_accountid_seq OWNER TO hmail;

--
-- Name: hm_accounts_accountid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_accounts_accountid_seq OWNED BY public.hm_accounts.accountid;


--
-- Name: hm_acl; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_acl (
    aclid bigint NOT NULL,
    aclsharefolderid bigint NOT NULL,
    aclpermissiontype smallint NOT NULL,
    aclpermissiongroupid bigint NOT NULL,
    aclpermissionaccountid bigint NOT NULL,
    aclvalue bigint NOT NULL
);


ALTER TABLE public.hm_acl OWNER TO hmail;

--
-- Name: hm_acl_aclid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_acl_aclid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_acl_aclid_seq OWNER TO hmail;

--
-- Name: hm_acl_aclid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_acl_aclid_seq OWNED BY public.hm_acl.aclid;


--
-- Name: hm_aliases; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_aliases (
    aliasid bigint NOT NULL,
    aliasdomainid integer NOT NULL,
    aliasname character varying(255) NOT NULL,
    aliasvalue character varying(255) NOT NULL,
    aliasactive smallint NOT NULL
);


ALTER TABLE public.hm_aliases OWNER TO hmail;

--
-- Name: hm_aliases_aliasid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_aliases_aliasid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_aliases_aliasid_seq OWNER TO hmail;

--
-- Name: hm_aliases_aliasid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_aliases_aliasid_seq OWNED BY public.hm_aliases.aliasid;


--
-- Name: hm_blocked_attachments; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_blocked_attachments (
    baid bigint NOT NULL,
    bawildcard character varying(255) NOT NULL,
    badescription character varying(255) NOT NULL
);


ALTER TABLE public.hm_blocked_attachments OWNER TO hmail;

--
-- Name: hm_blocked_attachments_baid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_blocked_attachments_baid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_blocked_attachments_baid_seq OWNER TO hmail;

--
-- Name: hm_blocked_attachments_baid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_blocked_attachments_baid_seq OWNED BY public.hm_blocked_attachments.baid;


--
-- Name: hm_dbversion; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_dbversion (
    value integer NOT NULL
);


ALTER TABLE public.hm_dbversion OWNER TO hmail;

--
-- Name: hm_distributionlists; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_distributionlists (
    distributionlistid bigint NOT NULL,
    distributionlistdomainid integer NOT NULL,
    distributionlistaddress character varying(255) NOT NULL,
    distributionlistenabled smallint NOT NULL,
    distributionlistrequireauth smallint NOT NULL,
    distributionlistrequireaddress character varying(255) NOT NULL,
    distributionlistmode smallint NOT NULL
);


ALTER TABLE public.hm_distributionlists OWNER TO hmail;

--
-- Name: hm_distributionlists_distributionlistid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_distributionlists_distributionlistid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_distributionlists_distributionlistid_seq OWNER TO hmail;

--
-- Name: hm_distributionlists_distributionlistid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_distributionlists_distributionlistid_seq OWNED BY public.hm_distributionlists.distributionlistid;


--
-- Name: hm_distributionlistsrecipients; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_distributionlistsrecipients (
    distributionlistrecipientid bigint NOT NULL,
    distributionlistrecipientlistid integer NOT NULL,
    distributionlistrecipientaddress character varying(255)
);


ALTER TABLE public.hm_distributionlistsrecipients OWNER TO hmail;

--
-- Name: hm_distributionlistsrecipients_distributionlistrecipientid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_distributionlistsrecipients_distributionlistrecipientid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_distributionlistsrecipients_distributionlistrecipientid_seq OWNER TO hmail;

--
-- Name: hm_distributionlistsrecipients_distributionlistrecipientid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_distributionlistsrecipients_distributionlistrecipientid_seq OWNED BY public.hm_distributionlistsrecipients.distributionlistrecipientid;


--
-- Name: hm_dnsbl; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_dnsbl (
    sblid bigint NOT NULL,
    sblactive smallint NOT NULL,
    sbldnshost character varying(255) NOT NULL,
    sblresult character varying(255) NOT NULL,
    sblrejectmessage character varying(255) NOT NULL,
    sblscore integer NOT NULL
);


ALTER TABLE public.hm_dnsbl OWNER TO hmail;

--
-- Name: hm_dnsbl_sblid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_dnsbl_sblid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_dnsbl_sblid_seq OWNER TO hmail;

--
-- Name: hm_dnsbl_sblid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_dnsbl_sblid_seq OWNED BY public.hm_dnsbl.sblid;


--
-- Name: hm_domain_aliases; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_domain_aliases (
    daid bigint NOT NULL,
    dadomainid integer NOT NULL,
    daalias character varying(255) NOT NULL
);


ALTER TABLE public.hm_domain_aliases OWNER TO hmail;

--
-- Name: hm_domain_aliases_daid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_domain_aliases_daid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_domain_aliases_daid_seq OWNER TO hmail;

--
-- Name: hm_domain_aliases_daid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_domain_aliases_daid_seq OWNED BY public.hm_domain_aliases.daid;


--
-- Name: hm_domains; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_domains (
    domainid bigint NOT NULL,
    domainname character varying(80) NOT NULL,
    domainactive smallint NOT NULL,
    domainpostmaster character varying(80) NOT NULL,
    domainmaxsize integer NOT NULL,
    domainaddomain character varying(255) NOT NULL,
    domainmaxmessagesize integer NOT NULL,
    domainuseplusaddressing smallint NOT NULL,
    domainplusaddressingchar character varying(1) NOT NULL,
    domainantispamoptions integer NOT NULL,
    domainenablesignature smallint NOT NULL,
    domainsignaturemethod smallint NOT NULL,
    domainsignatureplaintext text NOT NULL,
    domainsignaturehtml text NOT NULL,
    domainaddsignaturestoreplies smallint NOT NULL,
    domainaddsignaturestolocalemail smallint NOT NULL,
    domainmaxnoofaccounts integer NOT NULL,
    domainmaxnoofaliases integer NOT NULL,
    domainmaxnoofdistributionlists integer NOT NULL,
    domainlimitationsenabled integer NOT NULL,
    domainmaxaccountsize integer NOT NULL,
    domaindkimselector character varying(255) NOT NULL,
    domaindkimprivatekeyfile character varying(255) NOT NULL
);


ALTER TABLE public.hm_domains OWNER TO hmail;

--
-- Name: hm_domains_domainid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_domains_domainid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_domains_domainid_seq OWNER TO hmail;

--
-- Name: hm_domains_domainid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_domains_domainid_seq OWNED BY public.hm_domains.domainid;


--
-- Name: hm_fetchaccounts; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_fetchaccounts (
    faid bigint NOT NULL,
    faactive smallint NOT NULL,
    faaccountid integer NOT NULL,
    faaccountname character varying(255) NOT NULL,
    faserveraddress character varying(255) NOT NULL,
    faserverport integer NOT NULL,
    faservertype smallint NOT NULL,
    fausername character varying(255) NOT NULL,
    fapassword character varying(255) NOT NULL,
    faminutes integer NOT NULL,
    fanexttry timestamp without time zone NOT NULL,
    fadaystokeep integer NOT NULL,
    falocked smallint NOT NULL,
    faprocessmimerecipients smallint NOT NULL,
    faprocessmimedate smallint NOT NULL,
    faconnectionsecurity smallint NOT NULL,
    fauseantispam smallint NOT NULL,
    fauseantivirus smallint NOT NULL,
    faenablerouterecipients smallint NOT NULL,
    famimerecipientheaders character varying(255) DEFAULT 'To,CC,X-RCPT-TO,X-Envelope-To'::character varying NOT NULL
);


ALTER TABLE public.hm_fetchaccounts OWNER TO hmail;

--
-- Name: hm_fetchaccounts_faid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_fetchaccounts_faid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_fetchaccounts_faid_seq OWNER TO hmail;

--
-- Name: hm_fetchaccounts_faid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_fetchaccounts_faid_seq OWNED BY public.hm_fetchaccounts.faid;


--
-- Name: hm_fetchaccounts_uids; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_fetchaccounts_uids (
    uidid bigint NOT NULL,
    uidfaid integer NOT NULL,
    uidvalue character varying(255) NOT NULL,
    uidtime timestamp without time zone NOT NULL
);


ALTER TABLE public.hm_fetchaccounts_uids OWNER TO hmail;

--
-- Name: hm_fetchaccounts_uids_uidid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_fetchaccounts_uids_uidid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_fetchaccounts_uids_uidid_seq OWNER TO hmail;

--
-- Name: hm_fetchaccounts_uids_uidid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_fetchaccounts_uids_uidid_seq OWNED BY public.hm_fetchaccounts_uids.uidid;


--
-- Name: hm_greylisting_triplets; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_greylisting_triplets (
    glid bigint NOT NULL,
    glcreatetime timestamp without time zone NOT NULL,
    glblockendtime timestamp without time zone NOT NULL,
    gldeletetime timestamp without time zone NOT NULL,
    glipaddress1 bigint NOT NULL,
    glipaddress2 bigint,
    glsenderaddress character varying(200) NOT NULL,
    glrecipientaddress character varying(200) NOT NULL,
    glblockedcount integer NOT NULL,
    glpassedcount integer NOT NULL
);


ALTER TABLE public.hm_greylisting_triplets OWNER TO hmail;

--
-- Name: hm_greylisting_triplets_glid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_greylisting_triplets_glid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_greylisting_triplets_glid_seq OWNER TO hmail;

--
-- Name: hm_greylisting_triplets_glid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_greylisting_triplets_glid_seq OWNED BY public.hm_greylisting_triplets.glid;


--
-- Name: hm_greylisting_whiteaddresses; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_greylisting_whiteaddresses (
    whiteid bigint NOT NULL,
    whiteipaddress character varying(255) NOT NULL,
    whiteipdescription character varying(255) NOT NULL
);


ALTER TABLE public.hm_greylisting_whiteaddresses OWNER TO hmail;

--
-- Name: hm_greylisting_whiteaddresses_whiteid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_greylisting_whiteaddresses_whiteid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_greylisting_whiteaddresses_whiteid_seq OWNER TO hmail;

--
-- Name: hm_greylisting_whiteaddresses_whiteid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_greylisting_whiteaddresses_whiteid_seq OWNED BY public.hm_greylisting_whiteaddresses.whiteid;


--
-- Name: hm_group_members; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_group_members (
    memberid bigint NOT NULL,
    membergroupid bigint NOT NULL,
    memberaccountid bigint NOT NULL
);


ALTER TABLE public.hm_group_members OWNER TO hmail;

--
-- Name: hm_group_members_memberid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_group_members_memberid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_group_members_memberid_seq OWNER TO hmail;

--
-- Name: hm_group_members_memberid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_group_members_memberid_seq OWNED BY public.hm_group_members.memberid;


--
-- Name: hm_groups; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_groups (
    groupid bigint NOT NULL,
    groupname character varying(255)
);


ALTER TABLE public.hm_groups OWNER TO hmail;

--
-- Name: hm_groups_groupid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_groups_groupid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_groups_groupid_seq OWNER TO hmail;

--
-- Name: hm_groups_groupid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_groups_groupid_seq OWNED BY public.hm_groups.groupid;


--
-- Name: hm_imapfolders; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_imapfolders (
    folderid bigint NOT NULL,
    folderaccountid integer NOT NULL,
    folderparentid integer NOT NULL,
    foldername character varying(255) NOT NULL,
    folderissubscribed smallint NOT NULL,
    foldercreationtime timestamp without time zone NOT NULL,
    foldercurrentuid bigint NOT NULL
);


ALTER TABLE public.hm_imapfolders OWNER TO hmail;

--
-- Name: hm_imapfolders_folderid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_imapfolders_folderid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_imapfolders_folderid_seq OWNER TO hmail;

--
-- Name: hm_imapfolders_folderid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_imapfolders_folderid_seq OWNED BY public.hm_imapfolders.folderid;


--
-- Name: hm_incoming_relays; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_incoming_relays (
    relayid integer NOT NULL,
    relayname character varying(100) NOT NULL,
    relaylowerip1 bigint NOT NULL,
    relaylowerip2 bigint,
    relayupperip1 bigint NOT NULL,
    relayupperip2 bigint
);


ALTER TABLE public.hm_incoming_relays OWNER TO hmail;

--
-- Name: hm_incoming_relays_relayid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_incoming_relays_relayid_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_incoming_relays_relayid_seq OWNER TO hmail;

--
-- Name: hm_incoming_relays_relayid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_incoming_relays_relayid_seq OWNED BY public.hm_incoming_relays.relayid;


--
-- Name: hm_logon_failures; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_logon_failures (
    ipaddress1 bigint NOT NULL,
    ipaddress2 bigint,
    failuretime timestamp without time zone NOT NULL
);


ALTER TABLE public.hm_logon_failures OWNER TO hmail;

--
-- Name: hm_message_metadata; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_message_metadata (
    metadata_id bigint NOT NULL,
    metadata_accountid integer NOT NULL,
    metadata_folderid integer NOT NULL,
    metadata_messageid bigint NOT NULL,
    metadata_dateutc timestamp without time zone,
    metadata_from character varying(255) NOT NULL,
    metadata_subject character varying(255) NOT NULL,
    metadata_to character varying(255) NOT NULL,
    metadata_cc character varying(255) NOT NULL
);


ALTER TABLE public.hm_message_metadata OWNER TO hmail;

--
-- Name: hm_message_metadata_metadata_id_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_message_metadata_metadata_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_message_metadata_metadata_id_seq OWNER TO hmail;

--
-- Name: hm_message_metadata_metadata_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_message_metadata_metadata_id_seq OWNED BY public.hm_message_metadata.metadata_id;


--
-- Name: hm_messagerecipients; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_messagerecipients (
    recipientid bigint NOT NULL,
    recipientmessageid bigint NOT NULL,
    recipientaddress character varying(255) NOT NULL,
    recipientlocalaccountid integer NOT NULL,
    recipientoriginaladdress character varying(255) NOT NULL
);


ALTER TABLE public.hm_messagerecipients OWNER TO hmail;

--
-- Name: hm_messagerecipients_recipientid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_messagerecipients_recipientid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_messagerecipients_recipientid_seq OWNER TO hmail;

--
-- Name: hm_messagerecipients_recipientid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_messagerecipients_recipientid_seq OWNED BY public.hm_messagerecipients.recipientid;


--
-- Name: hm_messages; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_messages (
    messageid bigint NOT NULL,
    messageaccountid integer NOT NULL,
    messagefolderid integer DEFAULT 0 NOT NULL,
    messagefilename character varying(255) NOT NULL,
    messagetype smallint NOT NULL,
    messagefrom character varying(255) NOT NULL,
    messagesize bigint NOT NULL,
    messagecurnooftries integer NOT NULL,
    messagenexttrytime timestamp without time zone NOT NULL,
    messageflags smallint NOT NULL,
    messagecreatetime timestamp without time zone NOT NULL,
    messagelocked smallint NOT NULL,
    messageuid bigint NOT NULL
);


ALTER TABLE public.hm_messages OWNER TO hmail;

--
-- Name: hm_messages_messageid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_messages_messageid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_messages_messageid_seq OWNER TO hmail;

--
-- Name: hm_messages_messageid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_messages_messageid_seq OWNED BY public.hm_messages.messageid;


--
-- Name: hm_routeaddresses; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_routeaddresses (
    routeaddressid bigint NOT NULL,
    routeaddressrouteid integer NOT NULL,
    routeaddressaddress character varying(255) NOT NULL
);


ALTER TABLE public.hm_routeaddresses OWNER TO hmail;

--
-- Name: hm_routeaddresses_routeaddressid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_routeaddresses_routeaddressid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_routeaddresses_routeaddressid_seq OWNER TO hmail;

--
-- Name: hm_routeaddresses_routeaddressid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_routeaddresses_routeaddressid_seq OWNED BY public.hm_routeaddresses.routeaddressid;


--
-- Name: hm_routes; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_routes (
    routeid bigint NOT NULL,
    routedomainname character varying(255) NOT NULL,
    routedescription character varying(255) NOT NULL,
    routetargetsmthost character varying(255) NOT NULL,
    routetargetsmtport integer NOT NULL,
    routenooftries integer NOT NULL,
    routeminutesbetweentry integer NOT NULL,
    routealladdresses smallint NOT NULL,
    routeuseauthentication smallint NOT NULL,
    routeauthenticationusername character varying(255) NOT NULL,
    routeauthenticationpassword character varying(255) NOT NULL,
    routetreatsecurityaslocal smallint NOT NULL,
    routeconnectionsecurity smallint NOT NULL,
    routetreatsenderaslocaldomain smallint NOT NULL
);


ALTER TABLE public.hm_routes OWNER TO hmail;

--
-- Name: hm_routes_routeid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_routes_routeid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_routes_routeid_seq OWNER TO hmail;

--
-- Name: hm_routes_routeid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_routes_routeid_seq OWNED BY public.hm_routes.routeid;


--
-- Name: hm_rule_actions; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_rule_actions (
    actionid bigint NOT NULL,
    actionruleid integer NOT NULL,
    actiontype smallint NOT NULL,
    actionimapfolder character varying(255) NOT NULL,
    actionsubject character varying(255) NOT NULL,
    actionfromname character varying(255) NOT NULL,
    actionfromaddress character varying(255) NOT NULL,
    actionto character varying(255) NOT NULL,
    actionbody text NOT NULL,
    actionfilename character varying(255) NOT NULL,
    actionsortorder integer NOT NULL,
    actionscriptfunction character varying(255) NOT NULL,
    actionheader character varying(80) NOT NULL,
    actionvalue character varying(255) NOT NULL,
    actionrouteid integer NOT NULL
);


ALTER TABLE public.hm_rule_actions OWNER TO hmail;

--
-- Name: hm_rule_actions_actionid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_rule_actions_actionid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_rule_actions_actionid_seq OWNER TO hmail;

--
-- Name: hm_rule_actions_actionid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_rule_actions_actionid_seq OWNED BY public.hm_rule_actions.actionid;


--
-- Name: hm_rule_criterias; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_rule_criterias (
    criteriaid bigint NOT NULL,
    criteriaruleid integer NOT NULL,
    criteriausepredefined smallint NOT NULL,
    criteriapredefinedfield smallint NOT NULL,
    criteriaheadername character varying(255) NOT NULL,
    criteriamatchtype smallint NOT NULL,
    criteriamatchvalue character varying(255) NOT NULL
);


ALTER TABLE public.hm_rule_criterias OWNER TO hmail;

--
-- Name: hm_rule_criterias_criteriaid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_rule_criterias_criteriaid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_rule_criterias_criteriaid_seq OWNER TO hmail;

--
-- Name: hm_rule_criterias_criteriaid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_rule_criterias_criteriaid_seq OWNED BY public.hm_rule_criterias.criteriaid;


--
-- Name: hm_rules; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_rules (
    ruleid bigint NOT NULL,
    ruleaccountid integer NOT NULL,
    rulename character varying(100) NOT NULL,
    ruleactive smallint NOT NULL,
    ruleuseand smallint NOT NULL,
    rulesortorder integer NOT NULL
);


ALTER TABLE public.hm_rules OWNER TO hmail;

--
-- Name: hm_rules_ruleid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_rules_ruleid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_rules_ruleid_seq OWNER TO hmail;

--
-- Name: hm_rules_ruleid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_rules_ruleid_seq OWNED BY public.hm_rules.ruleid;


--
-- Name: hm_securityranges; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_securityranges (
    rangeid bigint NOT NULL,
    rangepriorityid integer NOT NULL,
    rangelowerip1 bigint NOT NULL,
    rangelowerip2 bigint,
    rangeupperip1 bigint NOT NULL,
    rangeupperip2 bigint,
    rangeoptions integer NOT NULL,
    rangename character varying(100) NOT NULL,
    rangeexpires smallint NOT NULL,
    rangeexpirestime timestamp without time zone NOT NULL
);


ALTER TABLE public.hm_securityranges OWNER TO hmail;

--
-- Name: hm_securityranges_rangeid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_securityranges_rangeid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_securityranges_rangeid_seq OWNER TO hmail;

--
-- Name: hm_securityranges_rangeid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_securityranges_rangeid_seq OWNED BY public.hm_securityranges.rangeid;


--
-- Name: hm_servermessages; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_servermessages (
    smid bigint NOT NULL,
    smname character varying(255) NOT NULL,
    smtext text NOT NULL
);


ALTER TABLE public.hm_servermessages OWNER TO hmail;

--
-- Name: hm_servermessages_smid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_servermessages_smid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_servermessages_smid_seq OWNER TO hmail;

--
-- Name: hm_servermessages_smid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_servermessages_smid_seq OWNED BY public.hm_servermessages.smid;


--
-- Name: hm_settings; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_settings (
    settingid bigint NOT NULL,
    settingname character varying(30) NOT NULL,
    settingstring character varying(4000) NOT NULL,
    settinginteger integer NOT NULL
);


ALTER TABLE public.hm_settings OWNER TO hmail;

--
-- Name: hm_settings_settingid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_settings_settingid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_settings_settingid_seq OWNER TO hmail;

--
-- Name: hm_settings_settingid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_settings_settingid_seq OWNED BY public.hm_settings.settingid;


--
-- Name: hm_sslcertificates; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_sslcertificates (
    sslcertificateid bigint NOT NULL,
    sslcertificatename character varying(255) NOT NULL,
    sslcertificatefile character varying(255) NOT NULL,
    sslprivatekeyfile character varying(255) NOT NULL
);


ALTER TABLE public.hm_sslcertificates OWNER TO hmail;

--
-- Name: hm_sslcertificates_sslcertificateid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_sslcertificates_sslcertificateid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_sslcertificates_sslcertificateid_seq OWNER TO hmail;

--
-- Name: hm_sslcertificates_sslcertificateid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_sslcertificates_sslcertificateid_seq OWNED BY public.hm_sslcertificates.sslcertificateid;


--
-- Name: hm_surblservers; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_surblservers (
    surblid bigint NOT NULL,
    surblactive smallint NOT NULL,
    surblhost character varying(255) NOT NULL,
    surblrejectmessage character varying(255) NOT NULL,
    surblscore integer NOT NULL
);


ALTER TABLE public.hm_surblservers OWNER TO hmail;

--
-- Name: hm_surblservers_surblid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_surblservers_surblid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_surblservers_surblid_seq OWNER TO hmail;

--
-- Name: hm_surblservers_surblid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_surblservers_surblid_seq OWNED BY public.hm_surblservers.surblid;


--
-- Name: hm_tcpipports; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_tcpipports (
    portid bigint NOT NULL,
    portprotocol smallint NOT NULL,
    portnumber integer NOT NULL,
    portaddress1 bigint NOT NULL,
    portaddress2 bigint,
    portconnectionsecurity smallint NOT NULL,
    portsslcertificateid bigint NOT NULL
);


ALTER TABLE public.hm_tcpipports OWNER TO hmail;

--
-- Name: hm_tcpipports_portid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_tcpipports_portid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_tcpipports_portid_seq OWNER TO hmail;

--
-- Name: hm_tcpipports_portid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_tcpipports_portid_seq OWNED BY public.hm_tcpipports.portid;


--
-- Name: hm_whitelist; Type: TABLE; Schema: public; Owner: hmail
--

CREATE TABLE public.hm_whitelist (
    whiteid bigint NOT NULL,
    whiteloweripaddress1 bigint NOT NULL,
    whiteloweripaddress2 bigint,
    whiteupperipaddress1 bigint NOT NULL,
    whiteupperipaddress2 bigint,
    whiteemailaddress character varying(255) NOT NULL,
    whitedescription character varying(255) NOT NULL
);


ALTER TABLE public.hm_whitelist OWNER TO hmail;

--
-- Name: hm_whitelist_whiteid_seq; Type: SEQUENCE; Schema: public; Owner: hmail
--

CREATE SEQUENCE public.hm_whitelist_whiteid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.hm_whitelist_whiteid_seq OWNER TO hmail;

--
-- Name: hm_whitelist_whiteid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: hmail
--

ALTER SEQUENCE public.hm_whitelist_whiteid_seq OWNED BY public.hm_whitelist.whiteid;


--
-- Name: hm_accounts accountid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_accounts ALTER COLUMN accountid SET DEFAULT nextval('public.hm_accounts_accountid_seq'::regclass);


--
-- Name: hm_acl aclid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_acl ALTER COLUMN aclid SET DEFAULT nextval('public.hm_acl_aclid_seq'::regclass);


--
-- Name: hm_aliases aliasid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_aliases ALTER COLUMN aliasid SET DEFAULT nextval('public.hm_aliases_aliasid_seq'::regclass);


--
-- Name: hm_blocked_attachments baid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_blocked_attachments ALTER COLUMN baid SET DEFAULT nextval('public.hm_blocked_attachments_baid_seq'::regclass);


--
-- Name: hm_distributionlists distributionlistid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_distributionlists ALTER COLUMN distributionlistid SET DEFAULT nextval('public.hm_distributionlists_distributionlistid_seq'::regclass);


--
-- Name: hm_distributionlistsrecipients distributionlistrecipientid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_distributionlistsrecipients ALTER COLUMN distributionlistrecipientid SET DEFAULT nextval('public.hm_distributionlistsrecipients_distributionlistrecipientid_seq'::regclass);


--
-- Name: hm_dnsbl sblid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_dnsbl ALTER COLUMN sblid SET DEFAULT nextval('public.hm_dnsbl_sblid_seq'::regclass);


--
-- Name: hm_domain_aliases daid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_domain_aliases ALTER COLUMN daid SET DEFAULT nextval('public.hm_domain_aliases_daid_seq'::regclass);


--
-- Name: hm_domains domainid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_domains ALTER COLUMN domainid SET DEFAULT nextval('public.hm_domains_domainid_seq'::regclass);


--
-- Name: hm_fetchaccounts faid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_fetchaccounts ALTER COLUMN faid SET DEFAULT nextval('public.hm_fetchaccounts_faid_seq'::regclass);


--
-- Name: hm_fetchaccounts_uids uidid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_fetchaccounts_uids ALTER COLUMN uidid SET DEFAULT nextval('public.hm_fetchaccounts_uids_uidid_seq'::regclass);


--
-- Name: hm_greylisting_triplets glid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_greylisting_triplets ALTER COLUMN glid SET DEFAULT nextval('public.hm_greylisting_triplets_glid_seq'::regclass);


--
-- Name: hm_greylisting_whiteaddresses whiteid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_greylisting_whiteaddresses ALTER COLUMN whiteid SET DEFAULT nextval('public.hm_greylisting_whiteaddresses_whiteid_seq'::regclass);


--
-- Name: hm_group_members memberid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_group_members ALTER COLUMN memberid SET DEFAULT nextval('public.hm_group_members_memberid_seq'::regclass);


--
-- Name: hm_groups groupid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_groups ALTER COLUMN groupid SET DEFAULT nextval('public.hm_groups_groupid_seq'::regclass);


--
-- Name: hm_imapfolders folderid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_imapfolders ALTER COLUMN folderid SET DEFAULT nextval('public.hm_imapfolders_folderid_seq'::regclass);


--
-- Name: hm_incoming_relays relayid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_incoming_relays ALTER COLUMN relayid SET DEFAULT nextval('public.hm_incoming_relays_relayid_seq'::regclass);


--
-- Name: hm_message_metadata metadata_id; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_message_metadata ALTER COLUMN metadata_id SET DEFAULT nextval('public.hm_message_metadata_metadata_id_seq'::regclass);


--
-- Name: hm_messagerecipients recipientid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_messagerecipients ALTER COLUMN recipientid SET DEFAULT nextval('public.hm_messagerecipients_recipientid_seq'::regclass);


--
-- Name: hm_messages messageid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_messages ALTER COLUMN messageid SET DEFAULT nextval('public.hm_messages_messageid_seq'::regclass);


--
-- Name: hm_routeaddresses routeaddressid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_routeaddresses ALTER COLUMN routeaddressid SET DEFAULT nextval('public.hm_routeaddresses_routeaddressid_seq'::regclass);


--
-- Name: hm_routes routeid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_routes ALTER COLUMN routeid SET DEFAULT nextval('public.hm_routes_routeid_seq'::regclass);


--
-- Name: hm_rule_actions actionid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_rule_actions ALTER COLUMN actionid SET DEFAULT nextval('public.hm_rule_actions_actionid_seq'::regclass);


--
-- Name: hm_rule_criterias criteriaid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_rule_criterias ALTER COLUMN criteriaid SET DEFAULT nextval('public.hm_rule_criterias_criteriaid_seq'::regclass);


--
-- Name: hm_rules ruleid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_rules ALTER COLUMN ruleid SET DEFAULT nextval('public.hm_rules_ruleid_seq'::regclass);


--
-- Name: hm_securityranges rangeid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_securityranges ALTER COLUMN rangeid SET DEFAULT nextval('public.hm_securityranges_rangeid_seq'::regclass);


--
-- Name: hm_servermessages smid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_servermessages ALTER COLUMN smid SET DEFAULT nextval('public.hm_servermessages_smid_seq'::regclass);


--
-- Name: hm_settings settingid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_settings ALTER COLUMN settingid SET DEFAULT nextval('public.hm_settings_settingid_seq'::regclass);


--
-- Name: hm_sslcertificates sslcertificateid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_sslcertificates ALTER COLUMN sslcertificateid SET DEFAULT nextval('public.hm_sslcertificates_sslcertificateid_seq'::regclass);


--
-- Name: hm_surblservers surblid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_surblservers ALTER COLUMN surblid SET DEFAULT nextval('public.hm_surblservers_surblid_seq'::regclass);


--
-- Name: hm_tcpipports portid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_tcpipports ALTER COLUMN portid SET DEFAULT nextval('public.hm_tcpipports_portid_seq'::regclass);


--
-- Name: hm_whitelist whiteid; Type: DEFAULT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_whitelist ALTER COLUMN whiteid SET DEFAULT nextval('public.hm_whitelist_whiteid_seq'::regclass);


--
-- Data for Name: hm_accounts; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_accounts (accountid, accountdomainid, accountadminlevel, accountaddress, accountpassword, accountactive, accountisad, accountaddomain, accountadusername, accountmaxsize, accountvacationmessageon, accountvacationmessage, accountvacationsubject, accountpwencryption, accountforwardenabled, accountforwardaddress, accountforwardkeeporiginal, accountenablesignature, accountsignatureplaintext, accountsignaturehtml, accountlastlogontime, accountvacationexpires, accountvacationexpiredate, accountpersonfirstname, accountpersonlastname) FROM stdin;
1	1	0	dravion@local.projects	0f6812347d544f42cdb8bd0a2e81f01cdf084e7aa224f0a18316bfc9d48d5747193d11	1	0			0	0			3	0		0	0			2023-08-02 15:34:04	0	2023-08-02 00:00:00		
2	3	0	postmaster@haircut24.biz	a0f7728be50847c63a1a6f4ce58b05a53680f918895861ee990ba18023607f6471c9df	1	0			0	0			3	0		0	0			2023-08-02 15:36:12	0	2023-08-02 00:00:00		
4	1	0	wp_en@local.projects	869233e32598d14bd4e384639e24dfb621d11a6d78bdbf1aa470a719d29c3f6de35ab1	1	0			0	0			3	0		0	0			2023-09-21 22:14:37	0	2023-08-02 00:00:00		
3	2	0	info@dravionsrealm.net	309861fe691ee76ebec2f0ae939df330a26fc28a227d7bb4849fc70fc65cb17256367f	1	0			0	0			3	0		0	0			2023-09-21 22:14:37	0	2023-08-02 00:00:00		
6	1	0	admin@local.projects	1ff58a7236192f19e3096218358cf15b4d76211eae68468ea9141806e8beaf28c513b7	1	0			0	0			3	0		0	0			2023-09-21 22:14:37	0	2023-08-26 00:00:00		
\.


--
-- Data for Name: hm_acl; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_acl (aclid, aclsharefolderid, aclpermissiontype, aclpermissiongroupid, aclpermissionaccountid, aclvalue) FROM stdin;
\.


--
-- Data for Name: hm_aliases; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_aliases (aliasid, aliasdomainid, aliasname, aliasvalue, aliasactive) FROM stdin;
1	1	foo@local.projects	xx@x	1
\.


--
-- Data for Name: hm_blocked_attachments; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_blocked_attachments (baid, bawildcard, badescription) FROM stdin;
1	*.bat	Batch processing file
2	*.cmd	Command file for Windows NT
3	*.com	Command
4	*.cpl	Windows Control Panel extension
5	*.csh	CSH script
6	*.exe	Executable file
7	*.inf	Setup file
8	*.lnk	Windows link file
9	*.msi	Windows Installer file
10	*.msp	Windows Installer patch
11	*.pif	Program Information file
12	*.reg	Registration key
13	*.scf	Windows Explorer command
14	*.scr	Windows Screen saver
\.


--
-- Data for Name: hm_dbversion; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_dbversion (value) FROM stdin;
5704
\.


--
-- Data for Name: hm_distributionlists; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_distributionlists (distributionlistid, distributionlistdomainid, distributionlistaddress, distributionlistenabled, distributionlistrequireauth, distributionlistrequireaddress, distributionlistmode) FROM stdin;
\.


--
-- Data for Name: hm_distributionlistsrecipients; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_distributionlistsrecipients (distributionlistrecipientid, distributionlistrecipientlistid, distributionlistrecipientaddress) FROM stdin;
\.


--
-- Data for Name: hm_dnsbl; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_dnsbl (sblid, sblactive, sbldnshost, sblresult, sblrejectmessage, sblscore) FROM stdin;
1	0	zen.spamhaus.org	127.0.0.2-8|127.0.0.10-11	Rejected by Spamhaus.	3
2	0	bl.spamcop.net	127.0.0.2	Rejected by SpamCop.	3
\.


--
-- Data for Name: hm_domain_aliases; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_domain_aliases (daid, dadomainid, daalias) FROM stdin;
\.


--
-- Data for Name: hm_domains; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_domains (domainid, domainname, domainactive, domainpostmaster, domainmaxsize, domainaddomain, domainmaxmessagesize, domainuseplusaddressing, domainplusaddressingchar, domainantispamoptions, domainenablesignature, domainsignaturemethod, domainsignatureplaintext, domainsignaturehtml, domainaddsignaturestoreplies, domainaddsignaturestolocalemail, domainmaxnoofaccounts, domainmaxnoofaliases, domainmaxnoofdistributionlists, domainlimitationsenabled, domainmaxaccountsize, domaindkimselector, domaindkimprivatekeyfile) FROM stdin;
1	local.projects	1		0		0	0		0	0	1			0	0	0	0	0	0	0		
2	dravionsrealm.net	1		0		0	0		0	0	1			0	0	0	0	0	0	0		
3	haircut24.biz	1		0		0	0		0	0	1			0	0	0	0	0	0	0		
\.


--
-- Data for Name: hm_fetchaccounts; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_fetchaccounts (faid, faactive, faaccountid, faaccountname, faserveraddress, faserverport, faservertype, fausername, fapassword, faminutes, fanexttry, fadaystokeep, falocked, faprocessmimerecipients, faprocessmimedate, faconnectionsecurity, fauseantispam, fauseantivirus, faenablerouterecipients, famimerecipientheaders) FROM stdin;
\.


--
-- Data for Name: hm_fetchaccounts_uids; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_fetchaccounts_uids (uidid, uidfaid, uidvalue, uidtime) FROM stdin;
\.


--
-- Data for Name: hm_greylisting_triplets; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_greylisting_triplets (glid, glcreatetime, glblockendtime, gldeletetime, glipaddress1, glipaddress2, glsenderaddress, glrecipientaddress, glblockedcount, glpassedcount) FROM stdin;
\.


--
-- Data for Name: hm_greylisting_whiteaddresses; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_greylisting_whiteaddresses (whiteid, whiteipaddress, whiteipdescription) FROM stdin;
\.


--
-- Data for Name: hm_group_members; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_group_members (memberid, membergroupid, memberaccountid) FROM stdin;
\.


--
-- Data for Name: hm_groups; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_groups (groupid, groupname) FROM stdin;
1	xxx
\.


--
-- Data for Name: hm_imapfolders; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_imapfolders (folderid, folderaccountid, folderparentid, foldername, folderissubscribed, foldercreationtime, foldercurrentuid) FROM stdin;
1	1	-1	INBOX	1	2023-08-02 15:34:04	0
2	2	-1	INBOX	1	2023-08-02 15:36:12	0
7	3	-1	Trash	1	2023-08-17 14:46:31	0
10	6	-1	INBOX	1	2023-08-26 20:32:01	38
6	4	-1	Sent	1	2023-08-02 15:44:01	17
5	4	-1	Trash	1	2023-08-02 15:43:48	59
8	3	-1	Sent	1	2023-08-17 14:46:59	3
3	3	-1	INBOX	1	2023-08-02 15:36:35	4
11	6	-1	Trash	1	2023-08-26 20:32:03	57
12	6	-1	Sent	1	2023-08-26 20:32:23	20
4	4	-1	INBOX	1	2023-08-02 15:43:44	57
\.


--
-- Data for Name: hm_incoming_relays; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_incoming_relays (relayid, relayname, relaylowerip1, relaylowerip2, relayupperip1, relayupperip2) FROM stdin;
1	xxx1	1	\N	1	\N
\.


--
-- Data for Name: hm_logon_failures; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_logon_failures (ipaddress1, ipaddress2, failuretime) FROM stdin;
\.


--
-- Data for Name: hm_message_metadata; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_message_metadata (metadata_id, metadata_accountid, metadata_folderid, metadata_messageid, metadata_dateutc, metadata_from, metadata_subject, metadata_to, metadata_cc) FROM stdin;
\.


--
-- Data for Name: hm_messagerecipients; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_messagerecipients (recipientid, recipientmessageid, recipientaddress, recipientlocalaccountid, recipientoriginaladdress) FROM stdin;
\.


--
-- Data for Name: hm_messages; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_messages (messageid, messageaccountid, messagefolderid, messagefilename, messagetype, messagefrom, messagesize, messagecurnooftries, messagenexttrytime, messageflags, messagecreatetime, messagelocked, messageuid) FROM stdin;
185	4	6	{0C41D803-702C-45D5-AD3E-B98A58E5C8F9}.eml	2		1001	0	1901-01-01 00:00:00	1	2023-09-20 19:05:36	0	9
168	4	6	{1A84389C-CACD-4AFD-AB85-5BC62D349630}.eml	2		404	0	1901-01-01 00:00:00	1	2023-09-20 14:32:43	0	7
228	4	4	{B4D9B0F2-8525-42C5-9A76-B9D47FD3D01A}.eml	2	admin@local.projects	782	0	1901-01-01 00:00:00	3	2023-09-21 16:50:18	1	54
234	4	4	{C96122CE-BC17-4CB7-9736-03F024066D61}.eml	2	wp_en@local.projects	818	0	1901-01-01 00:00:00	3	2023-09-21 18:27:56	1	56
184	6	10	{E7A00E50-DEF4-46C2-B939-0E63D2DD7AA5}.eml	2	wp_en@local.projects	1185	0	1901-01-01 00:00:00	75	2023-09-20 19:05:36	1	32
167	6	10	{50CCBCBF-7E5A-4AE0-B5F8-4C47ED4FCA61}.eml	2	wp_en@local.projects	588	0	1901-01-01 00:00:00	75	2023-09-20 14:32:43	1	30
211	6	10	{078D60AE-40FC-4992-93D4-13060EC1CA5B}.eml	2	wp_en@local.projects	782	0	1901-01-01 00:00:00	75	2023-09-20 23:02:15	1	36
190	6	10	{A26D1579-D9FA-480B-9CD5-80D8D84C60FF}.eml	2	wp_en@local.projects	1459	0	1901-01-01 00:00:00	75	2023-09-20 21:37:22	1	34
212	4	6	{1684D466-CD28-464C-A294-5E6B8F016983}.eml	2		598	0	1901-01-01 00:00:00	1	2023-09-20 23:02:15	0	13
226	6	10	{F56B0811-6225-48A4-A9A8-84CAF1062B8F}.eml	2	wp_en@local.projects	583	0	1901-01-01 00:00:00	11	2023-09-21 16:50:11	1	37
180	6	10	{D1817D50-950C-4A02-A688-9A99CAEBA9E7}.eml	2	wp_en@local.projects	923	0	1901-01-01 00:00:00	75	2023-09-20 18:31:33	1	31
227	4	6	{53C4F40D-445D-4F06-B018-ED3878C03B98}.eml	2		399	0	1901-01-01 00:00:00	1	2023-09-21 16:50:11	0	14
152	4	6	{0AC73C0B-AB75-4AC4-809B-C5B5E419A29A}.eml	2		400	0	1901-01-01 00:00:00	1	2023-09-20 12:11:17	0	4
235	4	6	{0C7B320D-51A4-4F11-8EA8-C009D03D021E}.eml	2		634	0	1901-01-01 00:00:00	1	2023-09-21 18:27:57	0	16
181	4	6	{FACC0A7E-0F25-4660-AAB8-933FF180D4DA}.eml	2		739	0	1901-01-01 00:00:00	1	2023-09-20 18:31:33	0	8
17	3	8	{0FA12E26-AB02-4367-9957-19895054B9E9}.eml	2		487	0	1901-01-01 00:00:00	1	2023-08-26 20:32:50	0	3
8	3	8	{94FA6208-2CBA-4D1C-B8FF-AC6FACFCA8ED}.eml	2		447	0	1901-01-01 00:00:00	1	2023-08-21 08:56:06	0	2
4	3	8	{E88D3CD7-AE86-4452-BCE7-33F3C80FAEAF}.eml	2		493	0	1901-01-01 00:00:00	1	2023-08-17 14:46:59	0	1
221	4	5	{45D99E74-AA9B-44BA-8978-3B55089E76BB}.eml	2	admin@local.projects	584	0	1901-01-01 00:00:00	75	2023-09-20 23:02:09	0	51
222	4	5	{ECC13839-047A-43F4-9F23-C7688A3E2D26}.eml	2	admin@local.projects	902	0	1901-01-01 00:00:00	67	2023-09-20 23:33:51	0	52
223	4	5	{8C233AEB-E2E8-427C-8141-75C449A886C8}.eml	2	admin@local.projects	903	0	1901-01-01 00:00:00	67	2023-09-20 23:44:12	0	53
224	4	5	{D529BF6E-61F7-4F9D-BB60-3479AE4F5798}.eml	2	admin@local.projects	899	0	1901-01-01 00:00:00	67	2023-09-20 23:54:49	0	54
225	4	5	{E20D0C56-D904-4683-AFBA-E65BEF701177}.eml	2	admin@local.projects	911	0	1901-01-01 00:00:00	67	2023-09-21 00:07:53	0	55
232	4	4	{5519EF49-6A5E-42BA-8A84-8F3C6D84B460}.eml	2	wp_en@local.projects	619	0	1901-01-01 00:00:00	11	2023-09-21 17:23:56	1	55
191	4	6	{1110011A-3A7A-447D-82E1-7ABB21E9E622}.eml	2		1275	0	1901-01-01 00:00:00	1	2023-09-20 21:37:22	0	11
189	4	6	{97F42777-5315-4CC1-AB43-40DCA905CEFF}.eml	2		1275	0	1901-01-01 00:00:00	1	2023-09-20 21:24:10	0	10
188	6	10	{C9AFDFBF-2486-44F3-BB5A-C99977F4FCFC}.eml	2	wp_en@local.projects	1459	0	1901-01-01 00:00:00	67	2023-09-20 21:24:10	1	33
236	6	10	{35D0C219-CAE6-4E90-BA5D-3DB48C12707E}.eml	2	wp_en@local.projects	583	0	1901-01-01 00:00:00	3	2023-09-21 18:28:21	1	38
150	4	6	{3A082898-0CE1-4F99-9B44-264D8619D5D6}.eml	2		600	0	1901-01-01 00:00:00	1	2023-09-20 10:55:34	0	3
233	4	6	{FC23C150-E8E7-46A3-A58F-A571D5B63DFD}.eml	2		435	0	1901-01-01 00:00:00	1	2023-09-21 17:23:57	0	15
237	4	6	{BEA55CDD-C2DB-43F6-AF2E-B761A559A2B5}.eml	2		399	0	1901-01-01 00:00:00	1	2023-09-21 18:28:21	0	17
230	4	5	{E4872724-DB17-48BA-A296-D99ABBD29777}.eml	2	admin@local.projects	782	0	1901-01-01 00:00:00	3	2023-09-21 16:50:18	0	56
231	4	5	{244096A1-70E4-42D1-A88A-8471A80A7F1D}.eml	2	admin@local.projects	782	0	1901-01-01 00:00:00	3	2023-09-21 16:50:18	0	57
194	6	10	{B6609436-9453-4853-82CA-97D98A68F100}.eml	2	wp_en@local.projects	1743	0	1901-01-01 00:00:00	75	2023-09-20 22:03:08	1	35
157	4	6	{AE7BEA42-B974-4A33-8CC1-2C83DEB5416F}.eml	2		600	0	1901-01-01 00:00:00	9	2023-09-20 12:32:02	0	5
195	4	6	{847C016B-097B-469F-A8C9-B337407B9DEC}.eml	2		1559	0	1901-01-01 00:00:00	1	2023-09-20 22:03:08	0	12
166	4	6	{279EB7DE-A615-41B1-A9BA-4C32218ABC2D}.eml	2		715	0	1901-01-01 00:00:00	1	2023-09-20 12:32:33	0	6
238	4	5	{C022257A-E1AC-4717-9580-9E3E5F94F2E5}.eml	2	wp_en@local.projects	619	0	1901-01-01 00:00:00	9	2023-09-21 17:23:56	0	58
239	4	5	{3C76011C-4D13-4A8A-B290-90E11F1EC44D}.eml	2	wp_en@local.projects	818	0	1901-01-01 00:00:00	1	2023-09-21 18:27:56	0	59
260	4	4	{1F42F337-2034-4C4C-80F2-3CA0F80CCA9B}.eml	2	admin@local.projects	584	0	1901-01-01 00:00:00	1	2023-09-21 20:21:13	1	57
261	6	12	{39B694D5-E99C-454A-870C-5721EE1319C8}.eml	2		400	0	1901-01-01 00:00:00	1	2023-09-21 20:21:13	0	20
18	3	3	{B5A368B5-E915-4189-8EFF-637EB7921AC8}.eml	2	admin@local.projects	899	0	1901-01-01 00:00:00	65	2023-08-26 20:32:55	1	4
9	3	3	{D432CC27-57E4-461F-9D9A-E352CB1EF326}.eml	2		803	0	1901-01-01 00:00:00	1	2023-08-21 20:04:35	1	3
5	3	3	{1B90C2A4-9FB9-46AA-8B8A-78B8D2DE39FC}.eml	2	wp_en@local.projects	670	0	1901-01-01 00:00:00	65	2023-08-17 14:47:16	1	2
3	3	3	{687BF4AC-0A5F-40D9-9A43-2632530EDB92}.eml	2	info@dravionsrealm.net	677	0	1901-01-01 00:00:00	65	2023-08-17 14:46:59	1	1
\.


--
-- Data for Name: hm_routeaddresses; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_routeaddresses (routeaddressid, routeaddressrouteid, routeaddressaddress) FROM stdin;
\.


--
-- Data for Name: hm_routes; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_routes (routeid, routedomainname, routedescription, routetargetsmthost, routetargetsmtport, routenooftries, routeminutesbetweentry, routealladdresses, routeuseauthentication, routeauthenticationusername, routeauthenticationpassword, routetreatsecurityaslocal, routeconnectionsecurity, routetreatsenderaslocaldomain) FROM stdin;
\.


--
-- Data for Name: hm_rule_actions; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_rule_actions (actionid, actionruleid, actiontype, actionimapfolder, actionsubject, actionfromname, actionfromaddress, actionto, actionbody, actionfilename, actionsortorder, actionscriptfunction, actionheader, actionvalue, actionrouteid) FROM stdin;
\.


--
-- Data for Name: hm_rule_criterias; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_rule_criterias (criteriaid, criteriaruleid, criteriausepredefined, criteriapredefinedfield, criteriaheadername, criteriamatchtype, criteriamatchvalue) FROM stdin;
\.


--
-- Data for Name: hm_rules; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_rules (ruleid, ruleaccountid, rulename, ruleactive, ruleuseand, rulesortorder) FROM stdin;
\.


--
-- Data for Name: hm_securityranges; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_securityranges (rangeid, rangepriorityid, rangelowerip1, rangelowerip2, rangeupperip1, rangeupperip2, rangeoptions, rangename, rangeexpires, rangeexpirestime) FROM stdin;
2	30	2130706433	\N	2130706433	\N	6091	My computer	0	2001-01-01 00:00:00
1	10	0	\N	4294967295	\N	6091	Internet	0	2001-01-01 00:00:00
\.


--
-- Data for Name: hm_servermessages; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_servermessages (smid, smname, smtext) FROM stdin;
1	VIRUS_FOUND	Virus found
2	VIRUS_ATTACHMENT_REMOVED	Virus found:\\r\\nThe attachment(s) of this message was removed since a virus was detected in at least one of them.\\r\\n\\r\\n
3	VIRUS_NOTIFICATION	The message below contained a virus and did not\r\nreach some or all of the intended recipients.\r\n\r\n   From: %MACRO_FROM%\r\n   To: %MACRO_TO%\r\n   Sent: %MACRO_SENT%\r\n   Subject: %MACRO_SUBJECT%\r\n\r\nhMailServer\r\n
4	SEND_FAILED_NOTIFICATION	Your message did not reach some or all of the intended recipients.\r\n\r\n   Sent: %MACRO_SENT%\r\n   Subject: %MACRO_SUBJECT%\r\n\r\nThe following recipient(s) could not be reached:\r\n\r\n%MACRO_RECIPIENTS%\r\n\r\nhMailServer\r\n
5	MESSAGE_UNDELIVERABLE	Message undeliverable
6	MESSAGE_FILE_MISSING	The mail server could not deliver the message to you since the file %MACRO_FILE% does not exist on the server.\r\n\r\nThe file may have been deleted by anti virus software running on the server.\r\n\r\nhMailServer
7	ATTACHMENT_REMOVED	The attachment %MACRO_FILE% was blocked for delivery by the e-mail server. Please contact your system administrator if you have any questions regarding this.\r\n\r\nhMailServer\r\n
\.


--
-- Data for Name: hm_settings; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_settings (settingid, settingname, settingstring, settinginteger) FROM stdin;
1	maxpop3connections		0
3	mirroremailaddress		0
4	relaymode		2
8	logdevice		0
11	protocolimap		1
12	protocolsmtp		1
13	protocolpop3		1
14	welcomeimap		0
15	welcomepop3		0
18	maxdelivertythreads		10
19	logformat		0
20	avclamwinenable		0
21	avclamwinexec		0
22	avclamwindb		0
23	avnotifysender		0
24	avnotifyreceiver		0
25	avaction		0
26	sendstatistics		0
29	smtprelayerpassword		0
32	usecustomvirusscanner		0
33	customvirusscannerexecutable		0
34	customviursscannerreturnvalue		0
35	usespf		0
36	usemxchecks		0
37	usescriptserver		0
38	scriptlanguage	VBScript	0
40	usecache		1
41	domaincachettl		60
42	accountcachettl		60
48	avmaxmsgsize		0
50	enableimapquota		1
51	enableimapidle		1
52	enableimapacl		1
53	maximapconnections		0
54	enableimapsort		1
55	workerthreadpriority		0
56	ascheckhostinhelo		0
57	tcpipthreads		15
59	usegreylisting		0
60	greylistinginitialdelay		30
61	greylistinginitialdelete		24
62	greylistingfinaldelete		864
63	antispamaddheaderspam		1
64	antispamaddheaderreason		1
65	antispamprependsubject		0
66	antispamprependsubjecttext	[SPAM]	0
67	enableattachmentblocking		0
71	aliascachettl		60
72	distributionlistcachettl		60
75	groupcachettl		60
76	imappublicfoldername	#Public	0
77	antispamenabled		0
78	usespfscore		3
79	ascheckhostinheloscore		2
80	usemxchecksscore		2
81	spammarkthreshold		5
82	spamdeletethreshold		20
83	spamassassinenabled		0
84	spamassassinscore		5
85	spamassassinmergescore		0
86	spamassassinhost	127.0.0.1	0
87	spamassassinport		783
88	antispammaxsize		1024
89	ASDKIMVerificationEnabled		0
90	ASDKIMVerificationFailureScore		5
95	IMAPHierarchyDelimiter	.	0
96	MaxNumberOfAsynchronousTasks		15
97	MessageIndexing		0
98	BypassGreylistingOnSPFSuccess		1
99	BypassGreylistingOnMailFromMX		0
101	ClamAVEnabled		0
102	ClamAVHost	localhost	0
103	ClamAVPort		3310
105	VerifyRemoteSslCertificate		1
106	SslCipherList	ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES256-GCM-SHA384:DHE-RSA-AES128-GCM-SHA256:DHE-DSS-AES128-GCM-SHA256:kEDH+AESGCM:ECDHE-RSA-AES128-SHA256:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA:ECDHE-ECDSA-AES256-SHA:DHE-RSA-AES128-SHA256:DHE-RSA-AES128-SHA:DHE-DSS-AES128-SHA256:DHE-RSA-AES256-SHA256:DHE-DSS-AES256-SHA:DHE-RSA-AES256-SHA:AES128-GCM-SHA256:AES256-GCM-SHA384:ECDHE-RSA-RC4-SHA:ECDHE-ECDSA-RC4-SHA:AES128:AES256:RC4-SHA:HIGH:!aNULL:!eNULL:!EXPORT:!DES:!3DES:!MD5:!PSK;	0
107	SslVersions		14
108	ImapMasterUser		0
109	ImapAuthAllowPlainText		0
110	EnableImapSASLPlain		0
111	EnableImapSASLInitialResponse		0
112	ascheckptr		0
113	ascheckptrscore		1
114	IPv6Preferred		0
45	backupoptions		15
91	AutoBanOnLogonFailureEnabled		0
47	defaultdomain	local.projects	0
92	MaxInvalidLogonAttempts		3
93	LogonAttemptsWithinMinutes		30
94	AutoBanMinutes		60
16	welcomesmtp	hMail Hello	0
43	awstatsenabled		1
7	logging		383
39	maxmessagesize		20480
9	smtpnoofretries		4
10	smtpminutesbetweenretries		60
104	SmtpDeliveryConnectionSecurity		2
27	hostname	camelot	0
17	smtprelayer		0
31	smtprelayerport		25
30	usesmtprelayerauthentication		0
28	smtprelayerusername		0
73	smtprelayerconnectionsecurity		0
5	authallowplaintext		0
6	allowmailfromnull		1
58	smtpallowincorrectlineendings		1
69	disconnectinvalidclients		0
70	maximumincorrectcommands		100
49	smtpdeliverybindtoip		0
68	maxsmtprecipientsinbatch		100
74	adddeliveredtoheader		0
44	rulelooplimit		5
100	MaxNumberOfMXHosts		15
2	maxsmtpconnections		0
46	backupdestination	D:\\\\\\\\ProgramData\\\\\\\\hMailServer\\\\\\\\backup	0
\.


--
-- Data for Name: hm_sslcertificates; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_sslcertificates (sslcertificateid, sslcertificatename, sslcertificatefile, sslprivatekeyfile) FROM stdin;
1	local.projects	C:\\\\hMailServer\\\\Certs\\\\local.projects.crt	C:\\\\hMailServer\\\\Certs\\\\local.projects.key
\.


--
-- Data for Name: hm_surblservers; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_surblservers (surblid, surblactive, surblhost, surblrejectmessage, surblscore) FROM stdin;
1	0	multi.surbl.org	Rejected by SURBL.	3
\.


--
-- Data for Name: hm_tcpipports; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_tcpipports (portid, portprotocol, portnumber, portaddress1, portaddress2, portconnectionsecurity, portsslcertificateid) FROM stdin;
1	1	25	0	\N	2	1
3	3	110	0	\N	3	1
4	5	143	0	\N	3	1
2	1	587	0	\N	3	1
\.


--
-- Data for Name: hm_whitelist; Type: TABLE DATA; Schema: public; Owner: hmail
--

COPY public.hm_whitelist (whiteid, whiteloweripaddress1, whiteloweripaddress2, whiteupperipaddress1, whiteupperipaddress2, whiteemailaddress, whitedescription) FROM stdin;
\.


--
-- Name: hm_accounts_accountid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_accounts_accountid_seq', 6, true);


--
-- Name: hm_acl_aclid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_acl_aclid_seq', 1, false);


--
-- Name: hm_aliases_aliasid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_aliases_aliasid_seq', 1, true);


--
-- Name: hm_blocked_attachments_baid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_blocked_attachments_baid_seq', 14, true);


--
-- Name: hm_distributionlists_distributionlistid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_distributionlists_distributionlistid_seq', 1, false);


--
-- Name: hm_distributionlistsrecipients_distributionlistrecipientid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_distributionlistsrecipients_distributionlistrecipientid_seq', 1, false);


--
-- Name: hm_dnsbl_sblid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_dnsbl_sblid_seq', 2, true);


--
-- Name: hm_domain_aliases_daid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_domain_aliases_daid_seq', 1, false);


--
-- Name: hm_domains_domainid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_domains_domainid_seq', 3, true);


--
-- Name: hm_fetchaccounts_faid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_fetchaccounts_faid_seq', 1, false);


--
-- Name: hm_fetchaccounts_uids_uidid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_fetchaccounts_uids_uidid_seq', 1, false);


--
-- Name: hm_greylisting_triplets_glid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_greylisting_triplets_glid_seq', 1, false);


--
-- Name: hm_greylisting_whiteaddresses_whiteid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_greylisting_whiteaddresses_whiteid_seq', 1, false);


--
-- Name: hm_group_members_memberid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_group_members_memberid_seq', 1, false);


--
-- Name: hm_groups_groupid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_groups_groupid_seq', 1, true);


--
-- Name: hm_imapfolders_folderid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_imapfolders_folderid_seq', 12, true);


--
-- Name: hm_incoming_relays_relayid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_incoming_relays_relayid_seq', 1, true);


--
-- Name: hm_message_metadata_metadata_id_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_message_metadata_metadata_id_seq', 1, false);


--
-- Name: hm_messagerecipients_recipientid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_messagerecipients_recipientid_seq', 105, true);


--
-- Name: hm_messages_messageid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_messages_messageid_seq', 261, true);


--
-- Name: hm_routeaddresses_routeaddressid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_routeaddresses_routeaddressid_seq', 1, false);


--
-- Name: hm_routes_routeid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_routes_routeid_seq', 1, false);


--
-- Name: hm_rule_actions_actionid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_rule_actions_actionid_seq', 1, false);


--
-- Name: hm_rule_criterias_criteriaid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_rule_criterias_criteriaid_seq', 1, false);


--
-- Name: hm_rules_ruleid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_rules_ruleid_seq', 1, false);


--
-- Name: hm_securityranges_rangeid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_securityranges_rangeid_seq', 2, true);


--
-- Name: hm_servermessages_smid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_servermessages_smid_seq', 7, true);


--
-- Name: hm_settings_settingid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_settings_settingid_seq', 114, true);


--
-- Name: hm_sslcertificates_sslcertificateid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_sslcertificates_sslcertificateid_seq', 1, true);


--
-- Name: hm_surblservers_surblid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_surblservers_surblid_seq', 1, true);


--
-- Name: hm_tcpipports_portid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_tcpipports_portid_seq', 4, true);


--
-- Name: hm_whitelist_whiteid_seq; Type: SEQUENCE SET; Schema: public; Owner: hmail
--

SELECT pg_catalog.setval('public.hm_whitelist_whiteid_seq', 1, false);


--
-- Name: hm_accounts hm_accounts_accountaddress_key; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_accounts
    ADD CONSTRAINT hm_accounts_accountaddress_key UNIQUE (accountaddress);


--
-- Name: hm_accounts hm_accounts_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_accounts
    ADD CONSTRAINT hm_accounts_pkey PRIMARY KEY (accountid);


--
-- Name: hm_acl hm_acl_aclsharefolderid_aclpermissiontype_aclpermissiongrou_key; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_acl
    ADD CONSTRAINT hm_acl_aclsharefolderid_aclpermissiontype_aclpermissiongrou_key UNIQUE (aclsharefolderid, aclpermissiontype, aclpermissiongroupid, aclpermissionaccountid);


--
-- Name: hm_acl hm_acl_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_acl
    ADD CONSTRAINT hm_acl_pkey PRIMARY KEY (aclid);


--
-- Name: hm_aliases hm_aliases_aliasname_key; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_aliases
    ADD CONSTRAINT hm_aliases_aliasname_key UNIQUE (aliasname);


--
-- Name: hm_aliases hm_aliases_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_aliases
    ADD CONSTRAINT hm_aliases_pkey PRIMARY KEY (aliasid);


--
-- Name: hm_blocked_attachments hm_blocked_attachments_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_blocked_attachments
    ADD CONSTRAINT hm_blocked_attachments_pkey PRIMARY KEY (baid);


--
-- Name: hm_distributionlists hm_distributionlists_distributionlistaddress_key; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_distributionlists
    ADD CONSTRAINT hm_distributionlists_distributionlistaddress_key UNIQUE (distributionlistaddress);


--
-- Name: hm_distributionlists hm_distributionlists_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_distributionlists
    ADD CONSTRAINT hm_distributionlists_pkey PRIMARY KEY (distributionlistid);


--
-- Name: hm_distributionlistsrecipients hm_distributionlistsrecipients_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_distributionlistsrecipients
    ADD CONSTRAINT hm_distributionlistsrecipients_pkey PRIMARY KEY (distributionlistrecipientid);


--
-- Name: hm_dnsbl hm_dnsbl_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_dnsbl
    ADD CONSTRAINT hm_dnsbl_pkey PRIMARY KEY (sblid);


--
-- Name: hm_domain_aliases hm_domain_aliases_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_domain_aliases
    ADD CONSTRAINT hm_domain_aliases_pkey PRIMARY KEY (daid);


--
-- Name: hm_domains hm_domains_domainname_key; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_domains
    ADD CONSTRAINT hm_domains_domainname_key UNIQUE (domainname);


--
-- Name: hm_domains hm_domains_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_domains
    ADD CONSTRAINT hm_domains_pkey PRIMARY KEY (domainid);


--
-- Name: hm_fetchaccounts hm_fetchaccounts_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_fetchaccounts
    ADD CONSTRAINT hm_fetchaccounts_pkey PRIMARY KEY (faid);


--
-- Name: hm_fetchaccounts_uids hm_fetchaccounts_uids_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_fetchaccounts_uids
    ADD CONSTRAINT hm_fetchaccounts_uids_pkey PRIMARY KEY (uidid);


--
-- Name: hm_greylisting_triplets hm_greylisting_triplets_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_greylisting_triplets
    ADD CONSTRAINT hm_greylisting_triplets_pkey PRIMARY KEY (glid);


--
-- Name: hm_greylisting_whiteaddresses hm_greylisting_whiteaddresses_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_greylisting_whiteaddresses
    ADD CONSTRAINT hm_greylisting_whiteaddresses_pkey PRIMARY KEY (whiteid);


--
-- Name: hm_group_members hm_group_members_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_group_members
    ADD CONSTRAINT hm_group_members_pkey PRIMARY KEY (memberid);


--
-- Name: hm_groups hm_groups_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_groups
    ADD CONSTRAINT hm_groups_pkey PRIMARY KEY (groupid);


--
-- Name: hm_imapfolders hm_imapfolders_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_imapfolders
    ADD CONSTRAINT hm_imapfolders_pkey PRIMARY KEY (folderid);


--
-- Name: hm_incoming_relays hm_incoming_relays_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_incoming_relays
    ADD CONSTRAINT hm_incoming_relays_pkey PRIMARY KEY (relayid);


--
-- Name: hm_message_metadata hm_message_metadata_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_message_metadata
    ADD CONSTRAINT hm_message_metadata_pkey PRIMARY KEY (metadata_id);


--
-- Name: hm_messagerecipients hm_messagerecipients_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_messagerecipients
    ADD CONSTRAINT hm_messagerecipients_pkey PRIMARY KEY (recipientid);


--
-- Name: hm_messages hm_messages_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_messages
    ADD CONSTRAINT hm_messages_pkey PRIMARY KEY (messageid);


--
-- Name: hm_routeaddresses hm_routeaddresses_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_routeaddresses
    ADD CONSTRAINT hm_routeaddresses_pkey PRIMARY KEY (routeaddressid);


--
-- Name: hm_routes hm_routes_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_routes
    ADD CONSTRAINT hm_routes_pkey PRIMARY KEY (routeid);


--
-- Name: hm_rule_actions hm_rule_actions_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_rule_actions
    ADD CONSTRAINT hm_rule_actions_pkey PRIMARY KEY (actionid);


--
-- Name: hm_rule_criterias hm_rule_criterias_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_rule_criterias
    ADD CONSTRAINT hm_rule_criterias_pkey PRIMARY KEY (criteriaid);


--
-- Name: hm_rules hm_rules_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_rules
    ADD CONSTRAINT hm_rules_pkey PRIMARY KEY (ruleid);


--
-- Name: hm_securityranges hm_securityranges_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_securityranges
    ADD CONSTRAINT hm_securityranges_pkey PRIMARY KEY (rangeid);


--
-- Name: hm_securityranges hm_securityranges_rangename_key; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_securityranges
    ADD CONSTRAINT hm_securityranges_rangename_key UNIQUE (rangename);


--
-- Name: hm_servermessages hm_servermessages_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_servermessages
    ADD CONSTRAINT hm_servermessages_pkey PRIMARY KEY (smid);


--
-- Name: hm_settings hm_settings_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_settings
    ADD CONSTRAINT hm_settings_pkey PRIMARY KEY (settingid);


--
-- Name: hm_settings hm_settings_settingname_key; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_settings
    ADD CONSTRAINT hm_settings_settingname_key UNIQUE (settingname);


--
-- Name: hm_sslcertificates hm_sslcertificates_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_sslcertificates
    ADD CONSTRAINT hm_sslcertificates_pkey PRIMARY KEY (sslcertificateid);


--
-- Name: hm_surblservers hm_surblservers_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_surblservers
    ADD CONSTRAINT hm_surblservers_pkey PRIMARY KEY (surblid);


--
-- Name: hm_tcpipports hm_tcpipports_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_tcpipports
    ADD CONSTRAINT hm_tcpipports_pkey PRIMARY KEY (portid);


--
-- Name: hm_whitelist hm_whitelist_pkey; Type: CONSTRAINT; Schema: public; Owner: hmail
--

ALTER TABLE ONLY public.hm_whitelist
    ADD CONSTRAINT hm_whitelist_pkey PRIMARY KEY (whiteid);


--
-- Name: idx_greylisting_triplets; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_greylisting_triplets ON public.hm_greylisting_triplets USING btree (glipaddress1, glipaddress2, glsenderaddress, glrecipientaddress);


--
-- Name: idx_hm_accounts; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_accounts ON public.hm_accounts USING btree (accountaddress);


--
-- Name: idx_hm_aliases; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_aliases ON public.hm_aliases USING btree (aliasdomainid, aliasname);


--
-- Name: idx_hm_distributionlists; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_distributionlists ON public.hm_distributionlists USING btree (distributionlistdomainid);


--
-- Name: idx_hm_distributionlistsrecipients; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_distributionlistsrecipients ON public.hm_distributionlistsrecipients USING btree (distributionlistrecipientlistid);


--
-- Name: idx_hm_domains; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_domains ON public.hm_domains USING btree (domainname);


--
-- Name: idx_hm_fetchaccounts_uids; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_fetchaccounts_uids ON public.hm_fetchaccounts_uids USING btree (uidfaid);


--
-- Name: idx_hm_imapfolders; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_imapfolders ON public.hm_imapfolders USING btree (folderaccountid);


--
-- Name: idx_hm_imapfolders_unique; Type: INDEX; Schema: public; Owner: hmail
--

CREATE UNIQUE INDEX idx_hm_imapfolders_unique ON public.hm_imapfolders USING btree (folderaccountid, folderparentid, foldername);


--
-- Name: idx_hm_logon_failures_failuretime; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_logon_failures_failuretime ON public.hm_logon_failures USING btree (failuretime);


--
-- Name: idx_hm_logon_failures_ipaddress; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_logon_failures_ipaddress ON public.hm_logon_failures USING btree (ipaddress1, ipaddress2);


--
-- Name: idx_hm_messagerecipients; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_messagerecipients ON public.hm_messagerecipients USING btree (recipientmessageid);


--
-- Name: idx_hm_messages; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_messages ON public.hm_messages USING btree (messageaccountid, messagefolderid);


--
-- Name: idx_hm_messages_type; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_hm_messages_type ON public.hm_messages USING btree (messagetype);


--
-- Name: idx_message_metadata_id; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_message_metadata_id ON public.hm_message_metadata USING btree (metadata_messageid);


--
-- Name: idx_message_metadata_unique; Type: INDEX; Schema: public; Owner: hmail
--

CREATE UNIQUE INDEX idx_message_metadata_unique ON public.hm_message_metadata USING btree (metadata_accountid, metadata_folderid, metadata_messageid);


--
-- Name: idx_rules; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_rules ON public.hm_rules USING btree (ruleaccountid);


--
-- Name: idx_rules_actions; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_rules_actions ON public.hm_rule_actions USING btree (actionruleid);


--
-- Name: idx_rules_criterias; Type: INDEX; Schema: public; Owner: hmail
--

CREATE INDEX idx_rules_criterias ON public.hm_rule_criterias USING btree (criteriaruleid);


--
-- PostgreSQL database dump complete
--

